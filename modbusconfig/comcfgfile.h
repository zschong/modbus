#ifndef __COM_CFG_FILE_H__
#define __COM_CFG_FILE_H__
#include <map>
#include <string>
#include "comconfig.h"
using namespace std;

class ComcfgFile
{
protected:
	string filename;
	map<unsigned,ComConfig> comcfgmap;
public:
	bool Store(void);
	bool Load(const string&);
	void SetComConfig(const ComConfig&);
public:
	map<unsigned,ComConfig>::iterator begin(void);
	map<unsigned,ComConfig>::iterator end(void);
public:
	typedef map<unsigned,ComConfig>::iterator Iterator;
};


#endif//__COM_CFG_FILE_H__
