#include "modbusmanager.h"

bool ModbusManager::SetComConfig(const ComConfig& com)
{
	int c = com.GetComId();
	int b = com.GetBaudRate();
	int p = com.GetParity();
	int z = com.GetByteSize();
	int s = com.GetStopBit();
	const string &n = idname.GetComName(c);
	
	if( modbusmap[c].SetComConfig(n, b, p, z, s) )
	{
		return true;
	}
	modbusmap.erase(c);
	return false;
}
bool ModbusManager::SetVarConfig(const VarConfig& var)
{
	int comid = var.GetComId();

	Iterator modbus = modbusmap.find( comid );

	if( modbusmap.end() == modbus )
	{
		return false;
	}

	int slave  = var.GetSlave();
	int fcode  = var.GetFcode();
	int offset = var.GetOffset();
	int count  = var.GetCount();
	int cmd    = var.GetCommand();
	VarOperator x(slave, fcode, offset, count);


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
			printf("VarCmdDel(%d,%08X)\n", comid, x.GetKey());
			cache.DelValue(comid, x.GetKey());
			modbus->second.DelVarConfig(x);
			break;
		default:
			return false;
	}
	return true;
}
bool ModbusManager::SetVarName(const VarName& var)
{
	int comid = varname.GetComId();

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
	idname.LoadComId(fname);
}
