#include <stdio.h>
#include "modbuscache.h"


//Value
Value::Value(void):value(0),id(0)
{
}
void Value::SetValue(const int v)
{
	value = ((unsigned)v) >> 16;
	t.init();
}
void Value::SetId(const unsigned i)
{
	id = i;
}
void Value::SetCom(const string& cm)
{
	com = cm;
}
void Value::SetName(const string& n)
{
	name = n;
}
const unsigned Value::GetValue(void) const
{
	return value;
}
const unsigned Value::GetId(void)const
{
	return id;
}
const string& Value::GetCom(void)const
{
	return com;
}
const string& Value::GetName(void)const
{
	return name;
}
const int Value::sdiff(void)const
{
	return t.sdiff();
}
const int Value::mdiff(void)const
{
	return t.mdiff();
}
const int Value::udiff(void)const
{
	return t.udiff();
}


//ModbusCache
bool ModbusCache::GetValue(list<Value>& vlist)
{
	for(map<string, map<int,Value> >::iterator A = valuemap.begin(); A != valuemap.end(); A++)
	{
		for(map<int,Value>::iterator B = A->second.begin(); B != A->second.end(); B++)
		{
			Value v = B->second;
			v.SetId(B->first);
			v.SetCom(A->first);
			vlist.push_back(v);
		}
	}
	return (vlist.begin() != vlist.end());
}
void ModbusCache::GetValue(void(*getvalue)(const Value&))
{
	if( 0 == getvalue )
	{
		return;
	}
	for(map<string, map<int,Value> >::iterator A = valuemap.begin(); A != valuemap.end(); A++)
	{
		for(map<int,Value>::iterator B = A->second.begin(); B != A->second.end(); B++)
		{
			Value v = B->second;
			v.SetId(B->first);
			v.SetCom(A->first);
			getvalue(v);
		}
	}
}
bool ModbusCache::SetName(const string& com, int id, const string& name)
{
	map<string,map<int,Value> >::iterator A = valuemap.find(com);

	if( valuemap.end() != A )
	{
		map<int,Value>::iterator B = A->second.find(id);
		if( A->second.end() != B )
		{
			B->second.SetName(name);
			return true;
		}
	}
	valuemap[com][id].SetName(name);
	return false;
}
bool ModbusCache::SetName(const string& com, int slave, int fcode, int offset, const string& name)
{
	int id = 0;
	
	id += (0x00ff & slave) << 24;
	id += (0x00ff & fcode) << 16;
	id += (0xffff & offset) << 0;

	return SetName(com, id, name);
}
void ModbusCache::SetValue(const string& com, int id, int value)
{
	valuemap[com][id].SetValue(value);
}
void ModbusCache::DelValue(const string& com, int id)
{
	map<string,map<int,Value> >::iterator value = valuemap.find(com);
	if( valuemap.end() != value )
	{
		value->second.erase(id);
	}
}
void ModbusCache::ShowValue(void)
{
	for(map<string,map<int,Value> >::iterator A = valuemap.begin(); A != valuemap.end(); A++)
	{
		for(map<int,Value>::iterator B = A->second.begin(); B != A->second.end(); B++)
		{
			printf("ModbusCache::%s(%s, %08X)\n", __func__, A->first.data(), B->first);
		}
	}
}
