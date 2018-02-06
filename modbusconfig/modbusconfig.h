#ifndef __MODBUS_CONFIG_H__
#define __MODBUS_CONFIG_H__
#include "varname.h"
#include "varconfig.h"
#include "comconfig.h"

typedef enum
{
	VAR_NAME = 0,
	VAR_CONFIG = 1,
	COM_CONFIG = 2,
}PacketType;

class ModbusConfig
{
	typedef enum
	{
		IndexPacketType = 0,
		IndexPacketObject = 1
	}IndexTypeDefine;
protected:
	unsigned char buffer[256];
public:
	ModbusConfig(void);
public:
	unsigned char* data(void);
	unsigned int length(void);
public:
	VarName& GetVarName(void);
	VarConfig& GetVarConfig(void);
	ComConfig& GetComConfig(void);
public:
	void SetType(int type);
	const int GetType(void);
};

#endif//__MODBUS_CONFIG_H__
