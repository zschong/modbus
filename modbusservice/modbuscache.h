#ifndef __MODBUS_CACHE_H__
#define __MODBUS_CACHE_H__
#include <map>
#include "modbusvalue.h"


class ModbusCache
{
protected:
	map<unsigned,map<unsigned,ModbusValue> > valuemap;
	typedef map<unsigned,ModbusValue>::iterator VIterator;
	typedef map<unsigned,map<unsigned,ModbusValue> >::iterator CVIterator;
public:
	bool GetValue(map<unsigned,map<unsigned,ModbusValue> >&);
	void SetVarName(unsigned comid, unsigned varid, const string&);
	void SetValue(unsigned comid, unsigned varid, unsigned value);
	void DelValue(unsigned comid, unsigned varid, unsigned count);
public:
	void ShowValue(map<unsigned,map<unsigned,ModbusValue> >&);
	void ShowValue(void);
};

#endif//__MODBUS_CACHE_H__
