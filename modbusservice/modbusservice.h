#ifndef __MODBUS_SERVICE_H__
#define __MODBUS_SERVICE_H__
#include <map>
#include <list>
#include <string>
#include "modbus.h"
#include "varname.h"
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
	bool GetValue(list<VarOperator>&);
	bool GetX01Response(list<VarOperator>&);
	bool GetX02Response(list<VarOperator>&);
	bool GetX03Response(list<VarOperator>&);
	bool GetX04Response(list<VarOperator>&);
	bool GetX05Response(list<VarOperator>&);
	bool GetX06Response(list<VarOperator>&);
	bool GetX0fResponse(list<VarOperator>&);
	bool GetX10Response(list<VarOperator>&);
public:
	map<unsigned,unsigned>& GetVarConfig(void);
};
#endif//__MODBUS_SERVICE_H__
