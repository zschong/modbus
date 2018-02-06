#include "modbusmanager.h"

bool ModbusManager::SetComConfig(const ComConfig& com)
{
	int c = com.GetComId();
	int b = com.GetBaudRate();
	int p = com.GetParity();
	int z = com.GetByteSize();
	int s = com.GetStopBit();
	const string &n = idfile.GetComName(c);
	
	if( modbusmap[c].SetComConfig(n, b, p, z, s) )
	{
		comcfg.SetComConfig(com);
		comcfg.Store();
		return true;
	}
	modbusmap.erase(c);
	return false;
}
bool ModbusManager::SetVarConfig(const VarConfig& var)
{
	int comid = var.GetComId();

	map<unsigned,ModbusService>::iterator modbus = modbusmap.find( comid );

	if( modbusmap.end() == modbus )
	{
		return false;
	}

	int slave  = var.GetSlave();
	int fcode  = var.GetFcode();
	int offset = var.GetOffset();
	int count  = var.GetCount();
	int cmd    = var.GetCommand();
	VarOperator x(slave, fcode, offset, count, 0xfff, comid);

	switch( cmd )
	{
		case VarCmdGet:
			break;
		case VarCmdSet:
			modbus->second.SetValue(x);
			break;
		case VarCmdAdd:
			modbus->second.AddVarConfig(x);
			break;
		case VarCmdDel:
			modbus->second.DelVarConfig(x);
			break;
		default:
			return false;
	}
	if( VarCmdAdd == cmd || VarCmdDel == cmd )
	{
		varcfg.SetVarConfig(comid, modbus->second.GetVarConfig());
		cache.DelValue(comid, x.GetKey());
		varcfg.Store();
	}
	return true;
}
bool ModbusManager::SetVarName(const VarName& var)
{
	int comid = var.GetComId();

	VarOperator x(var.GetSlave(), var.GetFcode(), var.GetOffset(), 0);

	cache.SetVarName(comid, x.GetKey(), var.GetVarName());
	return true;
}
void ModbusManager::RunLoop(void)
{
	for(Iterator i = modbusmap.begin(); i != modbusmap.end(); i++)
	{
		list<VarOperator> vlist;

		if( i->second.GetValue(vlist) )
		{
			typedef list<VarOperator>::iterator Literator;
			for(Literator v = vlist.begin(); v != vlist.end(); v++)
			{
				cache.SetValue(i->first, v->GetKey(), v->GetCount());
			}
		}
	}
}
bool ModbusManager::GetValue(map<unsigned,map<unsigned,ModbusValue> >& vmap)
{
	cache.GetValue(vmap);
}
void ModbusManager::LoadComId(const string& fname)
{
	idfile.Load(fname);
}
void ModbusManager::LoadComConfig(const string& fname)
{
	comcfg.Load(fname);

	for(ComcfgFile::Iterator i = comcfg.begin(); i != comcfg.end(); i++)
	{
		int c = i->second.GetComId();
		int b = i->second.GetBaudRate();
		int p = i->second.GetParity();
		int z = i->second.GetByteSize();
		int s = i->second.GetStopBit();
		const string &n = idfile.GetComName(c);
		
		modbusmap[c].SetComConfig(n, b, p, z, s);
	}
}
void ModbusManager::LoadVarConfig(const string& fname)
{
	varcfg.Load(fname);

	for(VarcfgFile::AIterator A = varcfg.begin(); A != varcfg.end(); A++)
	{
		for(VarcfgFile::BIterator B=A->second.begin(); B != A->second.end(); B++)
		{
			VarOperator x(B->first, B->second);
			modbusmap[A->first].AddVarConfig(x);
		}
	}
}
