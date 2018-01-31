#include "modbusvalue.h"

ModbusValue::ModbusValue(void):comid(0),value(0),varid(0)
{
}
ModbusValue::ModbusValue(const string& name, unsigned c, unsigned i, unsigned v)
:varname(name), comid(c), varid(i), value(v)
{
}
void ModbusValue::SetValue(const unsigned v)
{
	value = v;
	t.init();
}
void ModbusValue::SetVarId(const unsigned vid)
{
	varid = vid;
}
void ModbusValue::SetComId(const unsigned cid)
{
	comid = cid;
}
void ModbusValue::SetVarName(const string& name)
{
	varname = name;
}
const unsigned ModbusValue::GetValue(void) const
{
	return value;
}
const unsigned ModbusValue::GetVarId(void)const
{
	return varid;
}
const unsigned ModbusValue::GetComId(void)const
{
	return comid;
}
const string& ModbusValue::GetVarName(void)const
{
	return varname;
}
const int ModbusValue::sdiff(void)const
{
	return t.sdiff();
}
const int ModbusValue::mdiff(void)const
{
	return t.mdiff();
}
const int ModbusValue::udiff(void)const
{
	return t.udiff();
}
