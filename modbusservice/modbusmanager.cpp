#include "modbusmanager.h"

void ModbusManager::SetComId(const string& com, unsigned id)
{
	comidmap[ com ] = id;
	idcommap[ id  ] = com;
}
bool ModbusManager::SetComConfig(const ComConfig& comcfg)
{
	int comid = comcfg.GetComId();
	ICiterator com = idcommap.find(comid);

	if( idcommap.end() == com )
	{
		return false;
	}
	
	if( modbusmap[ comid ].SetComConfig(com->second, comcfg) )
	{
		return true;
	}
	modbusmap.erase( comid );
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
	RegisterOperator x(slave, fcode, offset, count);


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
bool ModbusManager::SetVarName(const VarName& v)
{
	int comid = v.GetComId();

	RegisterOperator x(v.GetSlave(), v.GetFcode(), v.GetOffset(), 0);

	cache.SetVarName(comid, x.GetKey(), v.GetVarName());
	return true;
}
void ModbusManager::RunLoop(void)
{
	for(Iterator i = modbusmap.begin(); i != modbusmap.end(); i++)
	{
		list<RegisterOperator> vlist;

		if( i->second.GetValue(vlist) )
		{
			typedef list<RegisterOperator>::iterator Literator;
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
bool ModbusManager::GetComConfig(map<string,map<unsigned,unsigned> >& ccmap)
{
}
bool ModbusManager::GetVarConfig(map<unsigned,map<unsigned,unsigned> >& idmap)
{
	map<unsigned,ModbusService>::iterator i;

	idmap.clear();
	for(i = modbusmap.begin(); i != modbusmap.end(); i++)
	{
		idmap[i->first] = i->second.GetVarConfig();
	}

	return idmap.begin() != idmap.end();
}
void ModbusManager::LoadComConfig(map<string,map<unsigned,unsigned> >& mmu)
{
}
void ModbusManager::LoadVarConfig(map<unsigned,map<unsigned,unsigned> >& mmu)
{
}
