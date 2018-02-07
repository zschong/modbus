#ifndef __MODBUS_SERVICE_H__
#define __MODBUS_SERVICE_H__
#include <map>
#include <list>
#include <string>
#include "modbus.h"
#include "varname.h"
#include "countfile.h"
#include "varconfig.h"
#include "varoperator.h"
#include "timeoperator.h"
using namespace std;

class ModbusService
{
protected:
	Modbus modbus;
	unsigned timeout;
	TimeOperator timer;
	list<VarOperator> requestlist;
	map<unsigned,unsigned> requestmap;
	map<unsigned,unsigned> srcount;
public:
	ModbusService(void);
public:
	bool SetValue(VarOperator&);
	void AddVarConfig(VarOperator&);
	void DelVarConfig(VarOperator&);
	bool SetComConfig(const string&, int,int,int,int);
protected:
	bool SendRequest(void);
	bool SendX01Request(VarOperator&);
	bool SendX02Request(VarOperator&);
	bool SendX03Request(VarOperator&);
	bool SendX04Request(VarOperator&);
	bool SendX05Request(VarOperator&);
	bool SendX06Request(VarOperator&);
	bool SendX0fRequest(VarOperator&);
	bool SendX10Request(VarOperator&);
public:
	unsigned GetValue(list<VarOperator>&);
	unsigned GetX01Response(list<VarOperator>&);
	unsigned GetX02Response(list<VarOperator>&);
	unsigned GetX03Response(list<VarOperator>&);
	unsigned GetX04Response(list<VarOperator>&);
	unsigned GetX05Response(list<VarOperator>&);
	unsigned GetX06Response(list<VarOperator>&);
	unsigned GetX0fResponse(list<VarOperator>&);
	unsigned GetX10Response(list<VarOperator>&);
public:
	map<unsigned,unsigned>& GetVarConfig(void);
	map<unsigned,SendRecvCount> GetCount(void);
};
#endif//__MODBUS_SERVICE_H__
