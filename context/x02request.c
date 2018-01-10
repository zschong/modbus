#include <stdio.h>
#include "modbuscrc16.h"
#include "x02request.h"

uint8_t X02RequestCheck(X02RequestContext* ctx)
{
	uint16_t count = X02RequestGetCount(ctx);

	if( X02RequestCalcCrc(ctx) != X02RequestGetCrc(ctx) )
	{
		return 0;
	}
	else if( count < X02RequestCountMin )
	{
		return 0;
	}
	else if( count > X02RequestCountMax )
	{
		return 0;
	}
	return 1;
}
uint8_t X02RequestGetSlave(X02RequestContext* ctx)
{
	return ctx->data[ X02RequestIndexSlave ];
}
uint8_t X02RequestGetFcode(X02RequestContext* ctx)
{
	return ctx->data[ X02RequestIndexFcode ];
}
uint16_t X02RequestGetOffset(X02RequestContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X02RequestIndexOffset0 ] << 8);
	s += (ctx->data[ X02RequestIndexOffset1 ] << 0);
	return s;
}
uint16_t X02RequestGetCount(X02RequestContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X02RequestIndexCount0 ] << 8);
	s += (ctx->data[ X02RequestIndexCount1 ] << 0);
	return s;
}
uint16_t X02RequestCalcCrc(X02RequestContext* ctx)
{
	return CRC16(ctx->data, X02RequestIndexMax-2);
}
uint16_t X02RequestGetCrc(X02RequestContext* ctx)
{
	uint16_t crc = 0;
	crc += (ctx->data[ (X02RequestIndexCrc0) ] << 0);
	crc += (ctx->data[ (X02RequestIndexCrc1) ] << 8);
	return crc;
}
uint8_t X02RequestGetLength(X02RequestContext* ctx)
{
	return X02RequestIndexMax;
}
void X02RequestSetSlave(X02RequestContext* ctx, uint8_t c)
{
	ctx->data[ X02RequestIndexSlave ] = c;
}
void X02RequestSetFcode(X02RequestContext* ctx, uint8_t c)
{
	ctx->data[ X02RequestIndexFcode ] = c;
}
void X02RequestSetOffset(X02RequestContext* ctx, uint16_t s)
{
	ctx->data[ X02RequestIndexOffset0 ] = (s >> 8);
	ctx->data[ X02RequestIndexOffset1 ] = (s >> 0);
}
void X02RequestSetCount(X02RequestContext* ctx, uint16_t s)
{
	if( s < X02RequestCountMin )
	{
		s = X02RequestCountMin;
	}
	else if( s > X02RequestCountMax )
	{
		s = X02RequestCountMax;
	}
	ctx->data[ X02RequestIndexCount0 ] = (s >> 8);
	ctx->data[ X02RequestIndexCount1 ] = (s >> 0);
}
void X02RequestSetCrc(X02RequestContext* ctx, uint16_t crc)
{
	ctx->data[ (X02RequestIndexCrc0) ] = (crc >> 0);
	ctx->data[ (X02RequestIndexCrc1) ] = (crc >> 8);
}

void X02RequestShowContext(X02RequestContext* ctx)
{
	int i = 0;
	int len = X02RequestGetLength(ctx);

	printf("X02Request:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx->data[i]);
	}
	printf("\b].%s\n", X02RequestCheck(ctx) == 1 ? "ok" : "xxxx");
}

#ifdef TEST_X02REQUEST
int main(void)
{
	X02RequestContext ctx;

	X02RequestSetSlave(&ctx, 0x01);
	X02RequestSetFcode(&ctx, 0x02);
	X02RequestSetOffset(&ctx, 0x0000);
	X02RequestSetCount(&ctx, 100);
	X02RequestSetCrc(&ctx, X02RequestCalcCrc(&ctx));

	X02RequestShowContext(&ctx);

	return 0;
}
#endif//TEST_X02REQUEST
