#ifndef __MODBUS_MANAGER_H__
#define __MODBUS_MANAGER_H__

class ModbusManager
{
protected:
	map<string,ModbusService> modbusmap;
	typedef map<string,ModbusService>::iterator Iterator;
public:
	bool ComConfig(ComConfig& comcfg)
	{
		string comname = var.GetComName();
		Iterator modbus = modbusmap.find(comname);

		if( modbusmap.end() != modbus )
		{
			return modbus->second.ComConfig(comcfg);
		}
		if( modbusmap[comname].ComConfig(comcfg) )
		{
			return true;
		}
		modbusmap.erase(comname);
		return false;
	}
	bool VarConfig(VarConfig& var)
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
				return modbus.AddVarConfig(first, second);
			case VarCmdDel:
				return modbus.DelVarConfig(first, second);
		}
		return false;
	}
};

#endif//__MODBUS_MANAGER_H__
