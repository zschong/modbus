#ifndef __COM_ID_FILE_H__
#define __COM_ID_FILE_H__
#include <map>
#include <string>
using namespace std;

class ComIdFile
{
protected:
	string nullname;
	string filename;
	map<unsigned,string> idname;
	map<string,unsigned> nameid;
public:
	bool Load(const string&);
public:
	void SetComId(const string& name, unsigned id);
public:
	const unsigned GetComId(const string& name);
	const string&  GetComName(const unsigned id);
};

#endif//__COM_ID_FILE_H__
