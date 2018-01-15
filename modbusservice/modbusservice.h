#ifndef __MODBUS_SERVICE_H__
#define __MODBUS_SERVICE_H__
#include <map>
#include <string>
#include "comconfig.h"
#include "varconfig.h"
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
public:
	bool ComConfig(ComConfig& c);
	void AddVarConfig(int offset, int count);
	void DelVarConfig(int offset, int count);
	bool SendX01Request(int first, int second);
	bool SendX02Request(int first, int second);
	bool SendX03Request(int first, int second);
	bool SendX04Request(int first, int second);
	bool SendRequest(void);
	bool GetValue(map<int,int>& values);
	bool SetValue(map<int,int>& values);
};

#endif//__MODBUS_SERVICE_H__

