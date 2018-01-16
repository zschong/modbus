#include "modbusconfig.h"


ConfigPacket::ConfigPacket(void)
{
	memset(buffer, 0, sizeof(buffer));
}
const int ConfigPacket::GetPacketType(void)
{
	return (int)buffer[ IndexPacketType ];
}
ComConfig& ConfigPacket::GetComConfig(void)
{
	return *(ComConfig*)(&buffer[ IndexPacketObject ]);
}
VarConfig& ConfigPacket::GetVarConfig(void)
{
	return *(VarConfig*)(&buffer[ IndexPacketObject ]);
}
void ConfigPacket::SetPacketType(const int type)
{
	buffer[ IndexPacketType ] = 0xff & type;
}
