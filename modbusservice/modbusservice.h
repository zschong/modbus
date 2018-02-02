#ifndef __MODBUS_SERVICE_H__
#define __MODBUS_SERVICE_H__
#include <map>
#include <list>
#include <string>
#include "modbus.h"
#include "varname.h"
#include "varconfig.h"
#include "comconfig.h"
#include "timeoperator.h"
#include "registeroperator.h"
using namespace std;


class ModbusService
{
protected:
	Modbus modbus;
	string comname;
	unsigned comid;
	unsigned timeout;
	ComConfig comconfig;
	TimeOperator timer;
	list<RegisterOperator> requestlist;
	map<unsigned,unsigned> requestmap;
	typedef map<unsigned,unsigned>::iterator Iterator;
public:
	ModbusService(void);
protected:
	bool SendRequest(void);
	bool SendX01Request(RegisterOperator&);
	bool SendX02Request(RegisterOperator&);
	bool SendX03Request(RegisterOperator&);
	bool SendX04Request(RegisterOperator&);
	bool SendX05Request(RegisterOperator&);
	bool SendX06Request(RegisterOperator&);
	bool SendX0fRequest(RegisterOperator&);
	bool SendX10Request(RegisterOperator&);
public:
	bool SetValue(RegisterOperator&);
	void AddVarConfig(RegisterOperator&);
	void DelVarConfig(RegisterOperator&);
	bool SetComConfig(const string&, const ComConfig&);
public:
	const ComConfig& GetComConfig(void);
	const map<unsigned,unsigned>& GetVarConfig(void);
public:
	bool GetValue(list<RegisterOperator>&);
	bool GetX01Response(list<RegisterOperator>&);
	bool GetX02Response(list<RegisterOperator>&);
	bool GetX03Response(list<RegisterOperator>&);
	bool GetX04Response(list<RegisterOperator>&);
	bool GetX05Response(list<RegisterOperator>&);
	bool GetX06Response(list<RegisterOperator>&);
	bool GetX0fResponse(list<RegisterOperator>&);
	bool GetX10Response(list<RegisterOperator>&);
};

#endif//__MODBUS_SERVICE_H__

