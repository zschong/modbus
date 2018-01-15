#ifndef __MODBUS_CONFIG_H__
#define __MODBUS_CONFIG_H__
#include "comconfig.h"
#include "varconfig.h"

class ConfigPacket
{
	typedef enum
	{
		IndexPacketType = 0,
		IndexPacketObject = 1
	}IndexTypeDefine;
	typedef enum
	{
		TypeComConfig = 0,
		TypeVarConfig = 1,
	}PacketTypeDefine;
protected:
	unsigned char buffer[255];
public:
	ConfigPacket(void);
public:
	const int GetPacketType(void);
	ComConfig& GetComConfig(void);
	VarConfig& GetVarConfig(void);
public:
	void SetPacketType(const int type);
};

#endif//__MODBUS_CONFIG_H__
