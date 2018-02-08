#ifndef __MODBUS_CACHE_H__
#define __MODBUS_CACHE_H__
#include <map>
#include "modbusvalue.h"
#include "timeoperator.h"

class ModbusCache
{
protected:
	map<unsigned,map<unsigned,TimeOperator> > delmap;
	map<unsigned,map<unsigned,ModbusValue> > valuemap;
public:
	bool GetValue(map<unsigned,map<unsigned,ModbusValue> >&);
	void SetVarName(unsigned comid, unsigned varid, const string&);
	void SetValue(unsigned comid, unsigned varid, unsigned value);
	void DelValue(unsigned comid, unsigned varid, unsigned count);
public:
	void ShowValue(map<unsigned,map<unsigned,ModbusValue> >&);
	void ShowValue(void);
	void DelByTime(void);
public:
	typedef map<unsigned,ModbusValue>::iterator BIterator;
	typedef map<unsigned,map<unsigned,ModbusValue> >::iterator AIterator;
};

#endif//__MODBUS_CACHE_H__
