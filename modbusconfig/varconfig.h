#ifndef __VAR_CONFIG_H__
#define __VAR_CONFIG_H__
#include <string>
#include <string.h>
#include "idcount.h"
using namespace std;

typedef enum
{
	VarCmdGet = 0,
	VarCmdSet = 1,
	VarCmdAdd = 2,
	VarCmdDel = 3
}CommandType;

class VarConfig
{
	typedef enum
	{
		IndexComNameA = 0,
		IndexComNameZ = 110,
		IndexCommand  = 111,
		IndexSlave    = 112,
		IndexFcode    = 113,
		IndexOffset0  = 114,
		IndexOffset1  = 115,
		IndexValue0   = 116,
		IndexValue1   = 117,
		IndexInterval = 118,
	}IndexTypeDefine;
protected:
	unsigned char buffer[128];

public:
	VarConfig(void);
	VarConfig(const string& comname, int cmd, IdCount& id);
	VarConfig(const string& comname, int cmd, int slave, int fcode, int offset, int value, int interval);
public:
	const string GetComName(void)const;
	const int GetCommand(void)const;
	const int GetSlave(void)const;
	const int GetFcode(void)const;
	const int GetOffset(void)const;
	const int GetCount(void)const;
	const int GetValue(void)const;
	const int GetInterval(void)const;
public:
	void SetComName(const string& comname);
	void SetCommand(const int cmd);
	void SetSlave(const int slave);
	void SetFcode(const int fcode);
	void SetOffset(const int offset);
	void SetCount(const int count);
	void SetValue(const int value);
	void SetInterval(const int interval);
public:
	VarConfig& operator=(const VarConfig& var);
public:
	void Show(void);
};
#endif//__VAR_CONFIG_H__
