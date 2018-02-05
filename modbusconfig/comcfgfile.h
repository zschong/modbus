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
public:
	void SetName(const string&);
public:
	bool Load(map<unsigned,ComConfig>&);
	bool Store(map<unsigned,ComConfig>&);
public:
	typedef map<unsigned,ComConfig>::iterator Iterator;
};


#endif//__COM_CFG_FILE_H__
