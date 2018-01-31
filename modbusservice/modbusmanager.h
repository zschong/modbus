#ifndef __MODBUS_MANAGER_H__
#define __MODBUS_MANAGER_H__
#include "modbuscache.h"
#include "modbusservice.h"

class ModbusManager
{
protected:
	ModbusCache cache;
	map<string,unsigned> comidmap;
	map<unsigned,string> idcommap;
	map<unsigned,ModbusService> modbusmap;
	typedef map<string,unsigned>::iterator CIiterator;
	typedef map<unsigned,string>::iterator ICiterator;
	typedef map<unsigned,ModbusService>::iterator Iterator;
public:
	void RunLoop(void);
	void SetComId(const string&, unsigned);
	bool SetValue(const string&, IdCount&);
	bool SetComConfig(const ComConfig& comcfg);
	bool SetVarConfig(const VarConfig& var);
	bool SetVarName(const VarName& var);
public:
	bool GetComConfig(map<unsigned,ComConfig>&);
	bool GetVarConfig(map<unsigned,map<unsigned,unsigned> >&);
	bool GetValue(map<unsigned, map<unsigned,ModbusValue> >&);
};

#endif//__MODBUS_MANAGER_H__
