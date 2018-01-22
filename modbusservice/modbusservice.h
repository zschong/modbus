#ifndef __MODBUS_SERVICE_H__
#define __MODBUS_SERVICE_H__
#include <map>
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
	map<int,int> requestmap;
	map<int,int> varconfigmap;
public:
	ModbusService(void);
protected:
	bool SendX01Request(int first, int second);
	bool SendX02Request(int first, int second);
	bool SendX03Request(int first, int second);
	bool SendX04Request(int first, int second);
	bool SendRequest(void);
public:
	bool SetValue(map<int,int>& values);
	bool SetComConfig(const ComConfig& c);
	void AddVarConfig(int offset, int count);
	void DelVarConfig(int offset, int count);
public:
	bool GetValue(map<int,int>& values);
	bool GetX01Response(map<int,int>& values);
	bool GetX02Response(map<int,int>& values);
	bool GetX03Response(map<int,int>& values);
	bool GetX04Response(map<int,int>& values);
	bool GetX05Response(map<int,int>& values);
	bool GetX06Response(map<int,int>& values);
	bool GetX0fResponse(map<int,int>& values);
	bool GetX10Response(map<int,int>& values);
};

#endif//__MODBUS_SERVICE_H__

