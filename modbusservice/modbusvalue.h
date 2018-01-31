#ifndef __MODBUS_VALUE_H__
#define __MODBUS_VALUE_H__
#include <string>
#include "timeoperator.h"
using namespace std;

class ModbusValue
{
protected:
	TimeOperator t;
	string varname;
	unsigned comid;
	unsigned value;
	unsigned varid;
public:
	ModbusValue(void);
	ModbusValue(const string&,unsigned,unsigned,unsigned);
public:
	void SetValue(const unsigned v);
	void SetVarId(const unsigned vid);
	void SetComId(const unsigned cid);
	void SetVarName(const string& name);
public:
	const unsigned GetValue(void)const;
	const unsigned GetVarId(void)const;
	const unsigned GetComId(void)const;
	const string&  GetVarName(void)const;
public:
	const int sdiff(void)const;
	const int mdiff(void)const;
	const int udiff(void)const;
};

#endif//__MODBUS_VALUE_H__
