#include "modbusconfig.h"


unsigned char* ModbusConfig::data(void)
{
	return buffer;
}
unsigned int ModbusConfig::length(void)
{
	return sizeof(buffer);
}
ModbusConfig::ModbusConfig(void)
{
	memset(buffer, 0, sizeof(buffer));
}
void ModbusConfig::SetType(const int type)
{
	buffer[ IndexPacketType ] = 0xff & type;
}
const int ModbusConfig::GetType(void)
{
	return (int)(buffer[ IndexPacketType ]);
}
VarName& ModbusConfig::GetVarName(void)
{
	return *(VarName*)(&buffer[ IndexPacketObject ]);
}
VarConfig& ModbusConfig::GetVarConfig(void)
{
	return *(VarConfig*)(&buffer[ IndexPacketObject ]);
}
ComConfig& ModbusConfig::GetComConfig(void)
{
	return *(ComConfig*)(&buffer[ IndexPacketObject ]);
}
