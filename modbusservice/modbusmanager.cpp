#include "modbusmanager.h"


bool ModbusManager::SetComConfig(const ComConfig& comcfg)
{
	string comname = comcfg.GetComName();
	Iterator modbus = modbusmap.find(comname);

	if( modbusmap.end() != modbus )
	{
		return modbus->second.SetComConfig(comcfg);
	}
	if( modbusmap[comname].SetComConfig(comcfg) )
	{
		return true;
	}
	modbusmap.erase(comname);
	return false;
}
bool ModbusManager::SetVarConfig(const VarConfig& var)
{
	string comname = var.GetComName();
	Iterator modbus = modbusmap.find(comname);

	if( modbusmap.end() == modbus )
	{
		return false;
	}
	int command = var.GetCommand();
	int slave = var.GetSlave();
	int fcode = var.GetFcode();
	int offset = var.GetOffset();
	int count = var.GetCount();
	int interval = var.GetInterval();
	IdCount x(slave, fcode, offset, count, interval);


	switch(command)
	{
		case VarCmdGet:
		case VarCmdSet:
		case VarCmdAdd:
			modbus->second.AddVarConfig(x);
			break;
		case VarCmdDel:
			modbus->second.DelVarConfig(x);
			cache.DelValue(comname, x.GetKey());
			break;
		default:
			return false;
	}
	return true;
}
bool ModbusManager::SetVarName(const VarName& v)
{
	IdCount x(v.GetSlave(), v.GetFcode(), v.GetOffset(), 0, 0);
	return cache.SetName(v.GetComName(), v.GetVarName(), x);
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
				IdCount x(v->GetKey(), v->GetValue());
				cache.SetValue(i->first, x);
			}
		}
	}
}
bool ModbusManager::GetValue(map<string, map<int,Value> >& vmap)
{
	return cache.GetValue(vmap);
}
