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
	int first = 0;
	int second = 0;

	first += ((0x00ff & slave)  << 24);
	first += ((0x00ff & fcode)  << 16);
	first += ((0xffff & offset) <<  0);
	second += ((0xffff & count) << 16);
	second += ((0x00ff & interval) << 8);

	switch(command)
	{
		case VarCmdGet:
		case VarCmdSet:
		case VarCmdAdd:
			modbus->second.AddVarConfig(first, second);
			break;
		case VarCmdDel:
			modbus->second.DelVarConfig(first, second);
			break;
		default:
			return false;
	}
	return true;
}
bool ModbusManager::GetValue(map<string, map<int, int> >& values)
{
	values.clear();
	for(Iterator i = modbusmap.begin(); i != modbusmap.end(); i++)
	{
		map<int,int> vii;
		if( i->second.GetValue(vii) )
		{
			values[i->first] = vii;
		}
	}
	return (values.begin() != values.end());
}
