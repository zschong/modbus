#ifndef __MODBUS_CACHE_H__
#define __MODBUS_CACHE_H__
#include <map>
#include <list>
#include <string>
#include "timeoperator.h"
using namespace std;

class Value
{
protected:
	string com;
	string name;
	TimeOperator t;
	unsigned value;
	unsigned id;
public:
	Value(void);
public:
	void SetValue(const int v);
	void SetId(const unsigned i);
	void SetCom(const string& cm);
	void SetName(const string& n);
public:
	const unsigned GetValue(void)const;
	const unsigned GetId(void)const;
	const string& GetCom(void)const;
	const string& GetName(void)const;
public:
	const int sdiff(void)const;
	const int mdiff(void)const;
	const int udiff(void)const;
};


class ModbusCache
{
protected:
	map<string,map<int,Value> > valuemap;
public:
	bool GetValue(list<Value>& vlist);
	bool GetValue(map<string, map<int,Value> >& vmap);
	void GetValue(void(*getvalue)(const Value&));
	bool SetName(const string& com, int id, const string& name);
	bool SetName(const string& com, int slave, int fcode, int offset, const string& name);
	void SetValue(const string& com, int id, int value);
	void SetValue(const string& com, int slave, int fcode, int offset, int value); 
	void DelValue(const string& com, int id);
	void ShowValue(void);
};

#endif//__MODBUS_CACHE_H__
