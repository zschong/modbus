#ifndef __VAR_NAME_H__
#define __VAR_NAME_H__
#include <string>
#include <string.h>
using namespace std;

class VarName
{
	typedef enum
	{
		IndexComNameA = 0,
		IndexComNameZ = 120,
		IndexVarNameA = 121,
		IndexVarNameZ = 240,
		IndexSlave    = 241,
		IndexFcode    = 242,
		IndexOffset0  = 243,
		IndexOffset1  = 244,
	}IndexTypeDefine;
protected:
	unsigned char buffer[250];

public:
	VarName(void);
	VarName(const string& comname, const string& varname, int slave, int fcode, int offset);
public:
	const string GetComName(void)const;
	const string GetVarName(void)const;
	const int GetCommand(void)const;
	const int GetSlave(void)const;
	const int GetFcode(void)const;
	const int GetOffset(void)const;
public:
	void SetComName(const string& comname);
	void SetVarName(const string& varname);
	void SetSlave(const int slave);
	void SetFcode(const int fcode);
	void SetOffset(const int offset);
	void SetCount(const int count);
public:
	VarName& operator=(const VarName& var);
};
#endif//__VAR_NAME_H__
