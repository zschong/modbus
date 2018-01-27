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
	map<string,string> sscom;
public:
	ValueFile(void);
	ValueFile(map<string, map<int,Value> >&);
public:
	void SetComMap(const string&, const string&);
	void MakeFile(map<string, map<int,Value> >&);
	void MakeSlaveFile(const string& f, list<Value>&);
	void MakeComFile(const string& f, map<int,Value>&);
	void MakeAllComFile(const string& f, map<string,list<Value> >&);
};

#endif//__VALUE_FILE_H__
