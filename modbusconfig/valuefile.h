#ifndef __VALUE_FILE_H__
#define __VALUE_FILE_H__
#include <map>
#include <string>
#include "modbusvalue.h"
using namespace std;

class ValueFile
{
protected:
	string filename;
public:
	void SetFileName(const string&);
public:
	bool Store(map<unsigned,map<unsigned,ModbusValue> >&);
public:
	typedef map<unsigned,map<unsigned,ModbusValue> >::iterator AIterator;
	typedef map<unsigned,ModbusValue>::iterator BIterator;
};


#endif//__VALUE_FILE_H__
