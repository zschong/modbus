#ifndef __VAR_CFG_FILE_H__
#define __VAR_CFG_FILE_H__
#include <map>
#include <string>
using namespace std;

class VarcfgFile
{
protected:
	string filename;
public:
	void SetName(const string&);
public:
	bool Load(map<unsigned,map<unsigned,unsigned> >&);
	bool Store(map<unsigned,map<unsigned,unsigned> >&);
public:
	typedef map<unsigned,unsigned>::iterator BIterator;
	typedef map<unsigned,map<unsigned,unsigned> >::iterator AIterator;
};


#endif//__VAR_CFG_FILE_H__
