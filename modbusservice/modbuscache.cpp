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
bool ModbusCache::GetValue(map<string, map<int,Value> >& vmap)
{
	vmap.clear();
	vmap = valuemap;
	return true;
}
bool ModbusCache::SetName(const string& com, const string& name, IdCount& x)
{
	map<string,map<int,Value> >::iterator A = valuemap.find(com);

	if( valuemap.end() != A )
	{
		map<int,Value>::iterator B = A->second.find( x.GetKey() );
		if( A->second.end() != B )
		{
			B->second.SetName(name);
			return true;
		}
	}
	valuemap[com][ x.GetKey() ].SetName(name);
	return false;
}
void ModbusCache::SetValue(const string& com, IdCount& x)
{
	valuemap[com][x.GetKey()].SetValue( x.GetValue() );
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
