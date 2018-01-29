#ifndef __MODBUS_SERVICE_H__
#define __MODBUS_SERVICE_H__
#include <map>
#include <list>
#include <string>
#include "modbus.h"
#include "varname.h"
#include "idcount.h"
#include "varconfig.h"
#include "comconfig.h"
#include "timeoperator.h"
using namespace std;


class ModbusService
{
protected:
	int timeout;
	Modbus modbus;
	string comname;
	TimeOperator timer;
	map<int,int> varconfigmap;
	list<IdCount> requestlist;
public:
	ModbusService(void);
protected:
	bool SendRequest(void);
	bool SendX01Request(IdCount&);
	bool SendX02Request(IdCount&);
	bool SendX03Request(IdCount&);
	bool SendX04Request(IdCount&);
	bool SendX05Request(IdCount&);
	bool SendX06Request(IdCount&);
	bool SendX0fRequest(IdCount&);
	bool SendX10Request(IdCount&);
public:
	bool SetValue(IdCount&);
	void AddVarConfig(IdCount&);
	void DelVarConfig(IdCount&);
	bool SetComConfig(const ComConfig& c);
public:
	bool GetValue(list<IdCount>&);
	bool GetX01Response(list<IdCount>&);
	bool GetX02Response(list<IdCount>&);
	bool GetX03Response(list<IdCount>&);
	bool GetX04Response(list<IdCount>&);
	bool GetX05Response(list<IdCount>&);
	bool GetX06Response(list<IdCount>&);
	bool GetX0fResponse(list<IdCount>&);
	bool GetX10Response(list<IdCount>&);
};

#endif//__MODBUS_SERVICE_H__

