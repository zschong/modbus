#ifndef __MODBUS_PACKET_H__
#define __MODBUS_PACKET_H__

typedef enum{
	PacketTypeX01 = 0x01,
	PacketTypeX02 = 0x02,
	PacketTypeX03 = 0x03,
	PacketTypeX04 = 0x04,
	PacketTypeX05 = 0x05,
	PacketTypeX06 = 0x06,
	PacketTypeX0f = 0x0f,
	PacketTypeX10 = 0x10,
}PacketType;

class X01RequestPacket
{
};
class X02RequestPacket
{
};
class X03RequestPacket
{
	typedef enum{
		IndexSlave = 0,
		IndexFcode = 1,
		IndexOffset0 = 2,
		IndexOffset1 = 3,
		IndexCount0 = 4,
		IndexCount1 = 5,
		IndexInterval0 = 6,
		IndexInterval1 = 7,
		IndexInterval2 = 8,
		IndexInterval3 = 9 
	}IndexType;
protected:
	unsigned char buffer[32];
public:
	X03RequestPacket(void);
public:
	unsigned char GetSlave(void);
	unsigned char GetFcode(void);
	unsigned short GetOffset(void);
	unsigned short GetCount(void);
	unsigned int GetInterval(void);
public:
	void SetSlave(unsigned char);
	void SetFcode(unsigned char);
	void SetOffset(unsigned short);
	void SetCount(unsigned short);
	void SetInterval(unsigned int);
};
class X04RequestPacket
{
};
class X05RequestPacket
{
};
class X06RequestPacket
{
};
class X0fRequestPacket
{
};
class X10RequestPacket
{
};

class X01ResponsePacket
{
};
class X02ResponsePacket
{
};
class X03ResponsePacket
{
};
class X04ResponsePacket
{
};
class X05ResponsePacket
{
};
class X06ResponsePacket
{
};
class X0fResponsePacket
{
};
class X10ResponsePacket
{
};


class ModbusPacket
{
protected:
	unsigned char buffer[128];

public:
	unsigned char GetPacketType(void);

public:
	X01RequestPacket& GetX01RequestPacket(void);
	X02RequestPacket& GetX02RequestPacket(void);
	X03RequestPacket& GetX03RequestPacket(void);
	X04RequestPacket& GetX04RequestPacket(void);
	X05RequestPacket& GetX05RequestPacket(void);
	X06RequestPacket& GetX06RequestPacket(void);
	X0fRequestPacket& GetX0fRequestPacket(void);
	X10RequestPacket& GetX10RequestPacket(void);

public:
	X01ResponsePacket& GetX01ResponsePacket(void);
	X02ResponsePacket& GetX02ResponsePacket(void);
	X03ResponsePacket& GetX03ResponsePacket(void);
	X04ResponsePacket& GetX04ResponsePacket(void);
	X05ResponsePacket& GetX05ResponsePacket(void);
	X06ResponsePacket& GetX06ResponsePacket(void);
	X0fResponsePacket& GetX0fResponsePacket(void);
	X10ResponsePacket& GetX10ResponsePacket(void);
};

#endif//__MODBUS_PACKET_H__
