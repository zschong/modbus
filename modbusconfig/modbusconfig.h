#ifndef __MODBUS_CONFIG_H__
#define __MODBUS_CONFIG_H__
#include "varname.h"
#include "varconfig.h"
#include "comconfig.h"

typedef enum
{
	TypeVarName = 0,
	TypeVarConfig = 1,
	TypeComConfig = 2,
}PacketTypeDefine;

class ModbusConfig
{
	typedef enum
	{
		IndexPacketType = 0,
		IndexPacketObject = 1
	}IndexTypeDefine;
protected:
	unsigned char buffer[255];
public:
	ModbusConfig(void);
public:
	unsigned char* data(void);
	unsigned int length(void);
public:
	VarName& GetVarName(void);
	VarConfig& GetVarConfig(void);
	ComConfig& GetComConfig(void);
	const int GetPacketType(void);
public:
	void SetPacketType(const int type);
};

#endif//__MODBUS_CONFIG_H__
