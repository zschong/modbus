#ifndef __VAR_CFG_FILE_H__
#define __VAR_CFG_FILE_H__
#include <map>
#include <string>
#include "varoperator.h"
using namespace std;

class VarcfgFile
{
protected:
	string filename;
	map<unsigned,map<unsigned,unsigned> > varcfgmap;
public:
	bool Store(void);
	bool Load(const string&);
	void SetVarConfig(unsigned, map<unsigned,unsigned>&);
public:
	map<unsigned,map<unsigned,unsigned> >::iterator begin(void);
	map<unsigned,map<unsigned,unsigned> >::iterator end(void);
public:
	typedef map<unsigned,unsigned>::iterator BIterator;
	typedef map<unsigned,map<unsigned,unsigned> >::iterator AIterator;
};


#endif//__VAR_CFG_FILE_H__
