#ifndef __VAR_CONFIG_H__
#define __VAR_CONFIG_H__
#include <string>
#include <string.h>
#include "registeroperator.h"
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
		IndexComId    = 0,
		IndexCommand  = 1,
		IndexSlave    = 2,
		IndexFcode    = 3,
		IndexOffset0  = 4,
		IndexOffset1  = 5,
		IndexValue0   = 6,
		IndexValue1   = 7
	}IndexTypeDefine;
protected:
	unsigned char buffer[8];

public:
	VarConfig(void);
	VarConfig(int comid, int cmd, RegisterOperator& roperator);
	VarConfig(int comid, int cmd, int slave, int fcode, int offset, int value);
public:
	const int GetComId(void)const;
	const int GetCommand(void)const;
	const int GetSlave(void)const;
	const int GetFcode(void)const;
	const int GetOffset(void)const;
	const int GetCount(void)const;
	const int GetValue(void)const;
public:
	void SetComId(const int comid);
	void SetCommand(const int cmd);
	void SetSlave(const int slave);
	void SetFcode(const int fcode);
	void SetOffset(const int offset);
	void SetCount(const int count);
	void SetValue(const int value);
public:
	VarConfig& operator=(const VarConfig& var);
public:
	void Show(void);
};
#endif//__VAR_CONFIG_H__
