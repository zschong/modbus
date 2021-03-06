#include <stdio.h>
#include "comconfig.h"


ComConfig::ComConfig(void)
{
	memset(buffer, 0, sizeof(buffer));
}
ComConfig::ComConfig(int comid, int baud, int parity, int bsize, int stop)
{
	SetComId(comid);
	SetBaudRate(baud);
	SetParity(parity);
	SetByteSize(bsize);
	SetStopBit(stop);
}
const int ComConfig::GetComId(void)const
{
	return (int)buffer[ IndexComId ];
}
const int ComConfig::GetBaudRate(void)const
{
	unsigned int baud = 0;

	baud += (buffer[ IndexBaudRate0 ] << 24);
	baud += (buffer[ IndexBaudRate1 ] << 16);
	baud += (buffer[ IndexBaudRate2 ] <<  8);
	baud += (buffer[ IndexBaudRate3 ] <<  0);

	return baud;
}
const int ComConfig::GetParity(void)const
{
	return (int)(buffer[ IndexParity ]);
}
const int ComConfig::GetByteSize(void)const
{
	return (int)(buffer[ IndexByteSize ]);
}
const int ComConfig::GetStopBit(void)const
{
	return (int)(buffer[ IndexStopBit ]);
}
void ComConfig::SetComId(const int comid)
{
	buffer[ IndexComId ] = 0xff & comid;
}
void ComConfig::SetBaudRate(const int baud)
{
	buffer[ IndexBaudRate0 ] = 0xFF & (baud >> 24);
	buffer[ IndexBaudRate1 ] = 0xFF & (baud >> 16);
	buffer[ IndexBaudRate2 ] = 0xFF & (baud >>  8);
	buffer[ IndexBaudRate3 ] = 0xFF & (baud >>  0);
}
void ComConfig::SetParity(const int parity)
{
	buffer[ IndexParity ] = 0xFF & parity;
}
void ComConfig::SetByteSize(const int bsize)
{
	buffer[ IndexByteSize ] = 0xFF & bsize;
}
void ComConfig::SetStopBit(const int stop)
{
	buffer[ IndexStopBit ] = 0xFF & stop;
}
ComConfig& ComConfig::operator=(const ComConfig& com)
{
	memcpy(buffer, com.buffer, sizeof(buffer));
	return *this;
}
void ComConfig::Show(void)
{
	printf("ComConfig");
	printf(".comid(%d)", GetComId());
	printf(".baud(%d)", GetBaudRate());
	printf(".parity(%d)", GetParity());
	printf(".bsize(%d)", GetByteSize());
	printf(".stop(%d)\n", GetStopBit());
}
