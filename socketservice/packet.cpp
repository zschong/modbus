#include <string.h>
#include "packet.h"

Packet::Packet(void)
{
	memset(buffer, 0, sizeof(buffer));
}
unsigned char* Packet::data(void)
{
	return buffer;
}
unsigned int Packet::size(void)
{
	return sizeof(buffer);
}
unsigned char Packet::type(void)
{
	return buffer[TypeIndex];
}
unsigned long long Packet::guid(void)
{
	union{
		unsigned short s;
		unsigned char c[2];
	}endian;
	union{
		unsigned long long ll;
		unsigned char c[sizeof(double)];
	}value;

	endian.s = 0xaabb;

	if( 0xaa == endian.c[0] )
	{
		value.c[ 0 ] = buffer[ ValueIndex0 ];
		value.c[ 1 ] = buffer[ ValueIndex1 ];
		value.c[ 2 ] = buffer[ ValueIndex2 ];
		value.c[ 3 ] = buffer[ ValueIndex3 ];
		value.c[ 4 ] = buffer[ ValueIndex4 ];
		value.c[ 5 ] = buffer[ ValueIndex5 ];
		value.c[ 6 ] = buffer[ ValueIndex6 ];
		value.c[ 7 ] = buffer[ ValueIndex7 ];
	}
	else
	{
		value.c[ 7 ] = buffer[ ValueIndex0 ];
		value.c[ 6 ] = buffer[ ValueIndex1 ];
		value.c[ 5 ] = buffer[ ValueIndex2 ];
		value.c[ 4 ] = buffer[ ValueIndex3 ];
		value.c[ 3 ] = buffer[ ValueIndex4 ];
		value.c[ 2 ] = buffer[ ValueIndex5 ];
		value.c[ 1 ] = buffer[ ValueIndex6 ];
		value.c[ 0 ] = buffer[ ValueIndex7 ];
	}

	return value.ll;
}
const double Packet::dvalue(void)
{
	union{
		unsigned short s;
		unsigned char c[2];
	}endian;
	union{
		double db;
		unsigned char c[sizeof(double)];
	}value;

	endian.s = 0xaabb;

	if( 0xaa == endian.c[0] )
	{
		value.c[ 0 ] = buffer[ ValueIndex0 ];
		value.c[ 1 ] = buffer[ ValueIndex1 ];
		value.c[ 2 ] = buffer[ ValueIndex2 ];
		value.c[ 3 ] = buffer[ ValueIndex3 ];
		value.c[ 4 ] = buffer[ ValueIndex4 ];
		value.c[ 5 ] = buffer[ ValueIndex5 ];
		value.c[ 6 ] = buffer[ ValueIndex6 ];
		value.c[ 7 ] = buffer[ ValueIndex7 ];
	}
	else
	{
		value.c[ 7 ] = buffer[ ValueIndex0 ];
		value.c[ 6 ] = buffer[ ValueIndex1 ];
		value.c[ 5 ] = buffer[ ValueIndex2 ];
		value.c[ 4 ] = buffer[ ValueIndex3 ];
		value.c[ 3 ] = buffer[ ValueIndex4 ];
		value.c[ 2 ] = buffer[ ValueIndex5 ];
		value.c[ 1 ] = buffer[ ValueIndex6 ];
		value.c[ 0 ] = buffer[ ValueIndex7 ];
	}

	return value.db;
}
unsigned int Packet::uvalue(void)
{
	union{
		unsigned short s;
		unsigned char c[2];
	}endian;
	union{
		unsigned int  u;
		unsigned char c[sizeof(double)];
	}value;

	endian.s = 0xaabb;

	if( 0xaa == endian.c[0] )
	{
		value.c[ 0 ] = buffer[ ValueIndex0 ];
		value.c[ 1 ] = buffer[ ValueIndex1 ];
		value.c[ 2 ] = buffer[ ValueIndex2 ];
		value.c[ 3 ] = buffer[ ValueIndex3 ];
	}
	else
	{
		value.c[ 3 ] = buffer[ ValueIndex0 ];
		value.c[ 2 ] = buffer[ ValueIndex1 ];
		value.c[ 1 ] = buffer[ ValueIndex2 ];
		value.c[ 0 ] = buffer[ ValueIndex3 ];
	}

	return value.u;
}
const char* Packet::svalue(void)
{
	buffer[LengthIndex-1] = 0;
	return (const char*)&buffer[ValueIndex0];
}
unsigned int Packet::length(void)
{
	return (unsigned int)buffer[LengthIndex];
}
const char* Packet::name(void)
{
	buffer[MaxIndex-1] = 0;
	return (const char*)&buffer[NameIndex];
}

void Packet::type(unsigned char t)
{
	buffer[TypeIndex] = t;
}
void Packet::guid(unsigned long long id)
{
	union{
		unsigned short s;
		unsigned char c[2];
	}endian;
	union{
		unsigned long long ll;
		unsigned char c[sizeof(double)];
	}value;

	value.ll = id;
	endian.s = 0xaabb;	
	if( 0xaa == endian.c[0] )
	{
		buffer[ GuidIndex0 ] = value.c[ 0 ];
		buffer[ GuidIndex1 ] = value.c[ 1 ];
		buffer[ GuidIndex2 ] = value.c[ 2 ];
		buffer[ GuidIndex3 ] = value.c[ 3 ];
		buffer[ GuidIndex4 ] = value.c[ 4 ];
		buffer[ GuidIndex5 ] = value.c[ 5 ];
		buffer[ GuidIndex6 ] = value.c[ 6 ];
		buffer[ GuidIndex7 ] = value.c[ 7 ];
	}
	else
	{
		buffer[ GuidIndex0 ] = value.c[ 7 ];
		buffer[ GuidIndex1 ] = value.c[ 6 ];
		buffer[ GuidIndex2 ] = value.c[ 5 ];
		buffer[ GuidIndex3 ] = value.c[ 4 ];
		buffer[ GuidIndex4 ] = value.c[ 3 ];
		buffer[ GuidIndex5 ] = value.c[ 2 ];
		buffer[ GuidIndex6 ] = value.c[ 1 ];
		buffer[ GuidIndex7 ] = value.c[ 0 ];
	}
}
void Packet::dvalue(const double &v)
{
	union{
		unsigned short s;
		unsigned char c[2];
	}endian;
	union{
		double db;
		unsigned char c[sizeof(double)];
	}value;

	value.db = v;
	endian.s = 0xaabb;	
	if( 0xaa == endian.c[0] )
	{
		buffer[ ValueIndex0 ] = value.c[ 0 ];
		buffer[ ValueIndex1 ] = value.c[ 1 ];
		buffer[ ValueIndex2 ] = value.c[ 2 ];
		buffer[ ValueIndex3 ] = value.c[ 3 ];
		buffer[ ValueIndex4 ] = value.c[ 4 ];
		buffer[ ValueIndex5 ] = value.c[ 5 ];
		buffer[ ValueIndex6 ] = value.c[ 6 ];
		buffer[ ValueIndex7 ] = value.c[ 7 ];
	}
	else
	{
		buffer[ ValueIndex0 ] = value.c[ 7 ];
		buffer[ ValueIndex1 ] = value.c[ 6 ];
		buffer[ ValueIndex2 ] = value.c[ 5 ];
		buffer[ ValueIndex3 ] = value.c[ 4 ];
		buffer[ ValueIndex4 ] = value.c[ 3 ];
		buffer[ ValueIndex5 ] = value.c[ 2 ];
		buffer[ ValueIndex6 ] = value.c[ 1 ];
		buffer[ ValueIndex7 ] = value.c[ 0 ];
	}
}
void Packet::uvalue(unsigned int v)
{
	union{
		unsigned short s;
		unsigned char c[2];
	}endian;
	union{
		unsigned int u;
		unsigned char c[sizeof(double)];
	}value;

	value.u = v;
	endian.s = 0xaabb;	
	if( 0xaa == endian.c[0] )
	{
		buffer[ ValueIndex0 ] = value.c[ 0 ];
		buffer[ ValueIndex1 ] = value.c[ 1 ];
		buffer[ ValueIndex2 ] = value.c[ 2 ];
		buffer[ ValueIndex3 ] = value.c[ 3 ];
	}
	else
	{
		buffer[ ValueIndex0 ] = value.c[ 3 ];
		buffer[ ValueIndex1 ] = value.c[ 2 ];
		buffer[ ValueIndex2 ] = value.c[ 1 ];
		buffer[ ValueIndex3 ] = value.c[ 0 ];
	}
}
bool Packet::svalue(const char *buf)
{
	int len = 0;

	if( NULL == buf )
	{
		return false;
	}
	if( (len = strlen(buf)) < 1 )
	{
		return false;
	}
	if( len > (LengthIndex - ValueIndex0 - 1) )
	{
		len = (LengthIndex - ValueIndex0 - 1);
	}
	memcpy(buffer+ValueIndex0, buf, len);
	buffer[ValueIndex0+len] = 0;
	return true;
}
bool Packet::name(const char *buf)
{
	int len = 0;

	if( NULL == buf )
	{
		return false;
	}
	if( (len = strlen(buf)) < 1 )
	{
		return false;
	}
	if( len > (MaxIndex - NameIndex - 1) )
	{
		len = (MaxIndex - NameIndex - 1);
	}
	memcpy(buffer+NameIndex, buf, len);
	buffer[NameIndex+len] = 0;
	return true;
}
