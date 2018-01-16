#ifndef __MODBUS_MANAGER_H__
#define __MODBUS_MANAGER_H__
#include "modbusservice.h"

class ModbusManager
{
protected:
	map<string,ModbusService> modbusmap;
	typedef map<string,ModbusService>::iterator Iterator;
public:
	bool SetComConfig(const ComConfig& comcfg);
	bool SetVarConfig(const VarConfig& var);
	bool GetValue(map<string, map<int,int> >& values);
};

#endif//__MODBUS_MANAGER_H__
