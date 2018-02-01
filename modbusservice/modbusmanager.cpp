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
	IdCount x(slave, fcode, offset, count);


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

	IdCount x(v.GetSlave(), v.GetFcode(), v.GetOffset(), 0);

	cache.SetVarName(comid, x.GetKey(), v.GetVarName());
	return true;
}
void ModbusManager::RunLoop(void)
{
	for(Iterator i = modbusmap.begin(); i != modbusmap.end(); i++)
	{
		list<IdCount> vlist;
		if( i->second.GetValue(vlist) )
		{
			for(list<IdCount>::iterator v = vlist.begin(); v != vlist.end(); v++)
			{
				cache.SetValue(i->first, v->GetKey(), v->GetValue());
			}
		}
	}
}
bool ModbusManager::GetValue(map<unsigned,map<unsigned,ModbusValue> >& vmap)
{
	cache.GetValue(vmap);
}
bool ModbusManager::GetComConfig(map<unsigned,ComConfig>& ccmap)
{
	map<unsigned,ModbusService>::iterator i;

	ccmap.clear();
	for(i = modbusmap.begin(); i != modbusmap.end(); i++)
	{
		ccmap[i->first] = i->second.GetComConfig();
	}

	return ccmap.begin() != ccmap.end();
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
