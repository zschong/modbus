#ifndef __VALUE_FILE_H__
#define __VALUE_FILE_H__
#include <map>
#include <list>
#include <string>
#include "modbuscache.h"
using namespace std;

class ValueFile
{
protected:
	string filename;
	typedef map<unsigned,ModbusValue>::iterator VIterator;
	typedef map<unsigned,map<unsigned,ModbusValue> >::iterator CVIterator;
public:
	ValueFile(void);
	ValueFile(const string&, map<unsigned, map<unsigned,ModbusValue> >&);
public:
	void SetFileName(const string& filename);
	void MakeFile(map<unsigned, map<unsigned,ModbusValue> >&);
	void MakeAllComFile(map<unsigned,map<unsigned,ModbusValue> >&);
	void MakeSlaveFile(unsigned, unsigned, list<ModbusValue>&);
	void MakeComFile(unsigned, map<unsigned,ModbusValue>&);
};

#endif//__VALUE_FILE_H__
