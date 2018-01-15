#ifndef __VAR_CONFIG_H__
#define __VAR_CONFIG_H__
#include <string.h>
#include <string>
using namespace std;

typedef enum
{
	VarCmdGet = 0,
	VarCmdSet = 1,
	VarCmdAdd = 2,
	VarCmdDel = 3,
}CommandType;

class VarConfig
{
	typedef enum
	{
		IndexComNameA = 0,
		IndexComNameZ = 120,
		IndexCommand  = 121,
		IndexSlave    = 122,
		IndexFcode    = 123,
		IndexOffset0  = 124,
		IndexOffset1  = 125,
		IndexValue0   = 126,
		IndexValue1   = 127,
	}IndexTypeDefine;
protected:
	unsigned char buffer[128];

public:
	VarConfig(void);
	VarConfig(const string& comname, int cmd, int slave, int fcode, int offset, int value);
public:
	const string GetComName(void);
	const int GetCommand(void);
	const int GetSlave(void);
	const int GetFcode(void);
	const int GetOffset(void);
	const int GetValue(void);
public:
	void SetComName(const string& comname);
	void SetCommand(const int cmd);
	void SetSlave(const int slave);
	void SetFcode(const int fcode);
	void SetOffset(const int offset);
	void SetValue(const int value);
};
#endif//__VAR_CONFIG_H__
