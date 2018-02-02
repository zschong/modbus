#ifndef __MCONFIG_FILE_H__
#define __MCONFIG_FILE_H__
#include <map>
#include <string>
using namespace std;

class MconfigFile
{
protected:
	string filename;
	typedef map<unsigned,unsigned>::iterator Iterator;
	typedef map<unsigned,map<unsigned,unsigned> >::iterator IIterator;
public:
	MconfigFile(void);
	MconfigFile(const string&);
public:
	void SetFileName(const string&);
public:
	bool WriteConfig(map<unsigned,map<unsigned,unsigned> >&);
	bool ReadConfig(map<unsigned,map<unsigned,unsigned> >&);
public:
	void Show(map<unsigned,map<unsigned,unsigned> >&);
};

#endif//__MCONFIG_FILE_H__
