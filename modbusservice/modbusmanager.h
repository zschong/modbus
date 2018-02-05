#ifndef __MODBUS_MANAGER_H__
#define __MODBUS_MANAGER_H__
#include "comconfig.h"
#include "comidname.h"
#include "comcfgfile.h"
#include "varcfgfile.h"
#include "modbuscache.h"
#include "modbusservice.h"

class ModbusManager
{
protected:
	ComIdName idname;
	ComcfgFile comcfg;
	VarcfgFile varcfg;
	ModbusCache cache;
	map<unsigned,ModbusService> modbusmap;
public:
	typedef map<unsigned,ModbusService>::iterator Iterator;
public:
	void RunLoop(void);
public:
	bool SetComConfig(const ComConfig& com);
	bool SetVarConfig(const VarConfig& var);
	bool SetVarName(const VarName& varname);
public:
	bool GetValue(map<unsigned,map<unsigned,ModbusValue> >&);
public:
	void LoadComId(const string&);
	void LoadComConfig(const string&);
	void LoadVarConfig(const string&);
};

#endif//__MODBUS_MANAGER_H__
