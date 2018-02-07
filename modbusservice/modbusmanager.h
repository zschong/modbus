#ifndef __MODBUS_MANAGER_H__
#define __MODBUS_MANAGER_H__
#include "valuefile.h"
#include "countfile.h"
#include "comconfig.h"
#include "comidfile.h"
#include "comcfgfile.h"
#include "varcfgfile.h"
#include "modbuscache.h"
#include "modbusservice.h"

class ModbusManager
{
protected:
	ComIdFile idfile;
	ComcfgFile comcfg;
	VarcfgFile varcfg;
	CountFile countfile;
	ValueFile valuefile;
	ModbusCache cache;
	map<unsigned,ModbusService> modbusmap;
	typedef map<unsigned,ModbusService>::iterator Iterator;
public:
	void RunLoop(void);
public:
	bool SetComConfig(const ComConfig& com);
	bool SetVarConfig(const VarConfig& var);
	bool SetVarName(const VarName& varname);
public:
	bool StoreCount(const string&);
	bool StoreValue(const string&);
public:
	void LoadComId(const string&);
	void LoadComConfig(const string&);
	void LoadVarConfig(const string&);
};

#endif//__MODBUS_MANAGER_H__
