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
			modbus->second.AddVarConfig(x.GetKey(), x.GetValue());
			break;
		case VarCmdDel:
			modbus->second.DelVarConfig(x.GetKey(), x.GetValue());
			cache.DelValue(comname, x.GetKey());
			break;
		default:
			return false;
	}
	return true;
}
bool ModbusManager::SetVarName(const VarName& var)
{
	return cache.SetName(var.GetComName(), var.GetSlave(), var.GetFcode(), var.GetOffset(), var.GetVarName());
}
void ModbusManager::RunLoop(void)
{
	for(Iterator i = modbusmap.begin(); i != modbusmap.end(); i++)
	{
		map<int,int> vmap;
		if( i->second.GetValue(vmap) )
		{
			for(map<int,int>::iterator v = vmap.begin(); v != vmap.end(); v++)
			{
				cache.SetValue(i->first, v->first, v->second);
			}
		}
	}
}
void ModbusManager::GetValue( void(*getvalue)(const Value&) )
{
	cache.GetValue(getvalue);
}
bool ModbusManager::GetValue(list<Value>& vlist)
{
	return cache.GetValue(vlist);
}
