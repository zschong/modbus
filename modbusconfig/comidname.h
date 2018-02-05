#ifndef __COM_ID_NAME_H__
#define __COM_ID_NAME_H__
#include <map>
#include <string>
using namespace std;

class ComIdName
{
protected:
	string nullname;
	string filename;
	map<unsigned,string> idname;
	map<string,unsigned> nameid;
public:
	bool LoadComId(const string&);
	void SetComId(const string& name, unsigned id);
public:
	unsigned GetComId(const string& name);
	const string& GetComName(unsigned id);
};

#endif//__COM_ID_NAME_H__
