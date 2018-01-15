#include <string.h>
#include "modbuspacket.h"

X03RequestPacket::X03RequestPacket(void)
{
	memset(buffer, 0, sizeof(buffer));
}
unsigned char X03RequestPacket::GetSlave(void)
{
	return buffer[ IndexSlave ];
}
unsigned char X03RequestPacket::GetFcode(void)
{
	return buffer[ IndexFcode ];
}
unsigned short X03RequestPacket::GetOffset(void)
{
	return (buffer[ IndexOffset0 ] << 8) | (buffer[ IndexOffset1 ] << 0);
}
unsigned short X03RequestPacket::GetCount(void)
{
	return (buffer[ IndexCount0 ] << 8) | (buffer[ IndexCount1 ] << 0);
}
unsigned int X03RequestPacket::GetInterval(void)
{
	return (buffer[ IndexInterval0 ] << 24)
		|| (buffer[ IndexInterval1 ] << 16)
		|| (buffer[ IndexInterval2 ] <<  8)
		|| (buffer[ IndexInterval3 ] <<  0);
}
void X03RequestPacket::SetSlave(unsigned char slave)
{
	buffer[ IndexSlave ] = slave;
}
void X03RequestPacket::SetFcode(unsigned char fcode)
{
	buffer[ IndexFcode ] = fcode;
}
void X03RequestPacket::SetOffset(unsigned short offset)
{
	buffer[ IndexOffset0 ] = offset >> 8;
	buffer[ IndexOffset1 ] = offset >> 0;
}
void X03RequestPacket::SetCount(unsigned short count)
{
	buffer[ IndexCount0 ] = count >> 8;
	buffer[ IndexCount1 ] = count >> 0;
}
void X03RequestPacket::SetInterval(unsigned int interval)
{
	buffer[ IndexInterval0 ] = (interval >> 24);
	buffer[ IndexInterval1 ] = (interval >> 16);
	buffer[ IndexInterval2 ] = (interval >>  8);
	buffer[ IndexInterval3 ] = (interval >>  0);
}

//ModbusPacket
unsigned char ModbusPacket::GetPacketType(void)
{
	return buffer[IndexPacketType];
}
X01RequestPacket& ModbusPacket::GetX01RequestPacket(void)
{
	return *(X01RequestPacket*)&buffer[IndexPacketBody];
}
X02RequestPacket& ModbusPacket::GetX02RequestPacket(void)
{
	return *(X02RequestPacket*)&buffer[IndexPacketBody];
}
X03RequestPacket& ModbusPacket::GetX03RequestPacket(void)
{
	return *(X03RequestPacket*)&buffer[IndexPacketBody];
}
X04RequestPacket& ModbusPacket::GetX04RequestPacket(void)
{
	return *(X04RequestPacket*)&buffer[IndexPacketBody];
}
X05RequestPacket& ModbusPacket::GetX05RequestPacket(void)
{
	return *(X05RequestPacket*)&buffer[IndexPacketBody];
}
X06RequestPacket& ModbusPacket::GetX06RequestPacket(void)
{
	return *(X06RequestPacket*)&buffer[IndexPacketBody];
}
X0fRequestPacket& ModbusPacket::GetX0fRequestPacket(void)
{
	return *(X0fRequestPacket*)&buffer[IndexPacketBody];
}
X10RequestPacket& ModbusPacket::GetX10RequestPacket(void)
{
	return *(X10RequestPacket*)&buffer[IndexPacketBody];
}

X01ResponsePacket& ModbusPacket::GetX01ResponsePacket(void)
{
	return *(X01ResponsePacket*)&buffer[IndexPacketBody];
}
X02ResponsePacket& ModbusPacket::GetX02ResponsePacket(void)
{
	return *(X02ResponsePacket*)&buffer[IndexPacketBody];
}
X03ResponsePacket& ModbusPacket::GetX03ResponsePacket(void)
{
	return *(X03ResponsePacket*)&buffer[IndexPacketBody];
}
X04ResponsePacket& ModbusPacket::GetX04ResponsePacket(void)
{
	return *(X04ResponsePacket*)&buffer[IndexPacketBody];
}
X05ResponsePacket& ModbusPacket::GetX05ResponsePacket(void)
{
	return *(X05ResponsePacket*)&buffer[IndexPacketBody];
}
X06ResponsePacket& ModbusPacket::GetX06ResponsePacket(void)
{
	return *(X06ResponsePacket*)&buffer[IndexPacketBody];
}
X0fResponsePacket& ModbusPacket::GetX0fResponsePacket(void)
{
	return *(X0fResponsePacket*)&buffer[IndexPacketBody];
}
X10ResponsePacket& ModbusPacket::GetX10ResponsePacket(void)
{
	return *(X10ResponsePacket*)&buffer[IndexPacketBody];
}
