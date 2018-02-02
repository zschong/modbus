#ifndef __MODBUS_CACHE_H__
#define __MODBUS_CACHE_H__
#include <map>
#include "modbusvalue.h"
#include "registeroperator.h"


class ModbusCache
{
protected:
	map<unsigned,map<unsigned,ModbusValue> > valuemap;
	typedef map<unsigned,ModbusValue>::iterator VIterator;
	typedef map<unsigned,map<unsigned,ModbusValue> >::iterator CVIterator;
public:
	bool GetValue(map<unsigned,map<unsigned,ModbusValue> >&);
	void SetVarName(unsigned cid, unsigned vid, const string& vname) ;
	void SetValue(unsigned cid, unsigned vid, unsigned value);
	void DelValue(unsigned cid, unsigned vid);
public:
	void ShowValue(map<unsigned,map<unsigned,ModbusValue> >&);
	void ShowValue(void);
};

#endif//__MODBUS_CACHE_H__
