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

