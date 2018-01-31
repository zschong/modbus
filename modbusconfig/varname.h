#ifndef __VAR_NAME_H__
#define __VAR_NAME_H__
#include <string>
#include <string.h>
using namespace std;

class VarName
{
	typedef enum
	{
		IndexComId    = 0,
		IndexSlave    = 1,
		IndexFcode    = 2,
		IndexOffset0  = 3,
		IndexOffset1  = 4,
		IndexVarNameA = 5,
		IndexVarNameZ = (IndexVarNameA + 128)
	}IndexTypeDefine;
protected:
	unsigned char buffer[IndexVarNameZ];

public:
	VarName(void);
	VarName(int comid, int slave, int fcode, int offset, const string& name);
public:
	const int GetComId(void)const;
	const int GetCommand(void)const;
	const int GetSlave(void)const;
	const int GetFcode(void)const;
	const int GetOffset(void)const;
	const string GetVarName(void)const;
public:
	void SetComId(const int comid);
	void SetSlave(const int slave);
	void SetFcode(const int fcode);
	void SetOffset(const int offset);
	void SetVarName(const string& varname);
public:
	VarName& operator=(const VarName& var);
public:
	void Show(void);
};
#endif//__VAR_NAME_H__
