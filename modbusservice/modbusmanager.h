#ifndef __MODBUS_MANAGER_H__
#define __MODBUS_MANAGER_H__
#include "modbuscache.h"
#include "modbusservice.h"

class ModbusManager
{
protected:
	ModbusCache cache;
	map<string,ModbusService> modbusmap;
	typedef map<string,ModbusService>::iterator Iterator;
public:
	void RunLoop(void);
	bool GetValue(list<Value>&);
	void GetValue(void(*get)(const Value&));
	bool SetComConfig(const ComConfig& comcfg);
	bool SetVarConfig(const VarConfig& var);
	bool SetVarName(const VarName& var);
};

#endif//__MODBUS_MANAGER_H__
