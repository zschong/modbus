#include <stdio.h>
#include "modbuscrc16.h"
#include "x01request.h"

uint8_t X01RequestCheck(X01RequestContext* ctx)
{
	uint16_t count = X01RequestGetCount(ctx);

	if( X01RequestCalcCrc(ctx) != X01RequestGetCrc(ctx) )
	{
		return 0;
	}
	else if( count < X01RequestCountMin )
	{
		return 0;
	}
	else if( count > X01RequestCountMax )
	{
		return 0;
	}
	return 1;
}
uint8_t X01RequestGetSlave(X01RequestContext* ctx)
{
	return ctx->data[ X01RequestIndexSlave ];
}
uint8_t X01RequestGetFcode(X01RequestContext* ctx)
{
	return ctx->data[ X01RequestIndexFcode ];
}
uint16_t X01RequestGetOffset(X01RequestContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X01RequestIndexOffset0 ] << 8);
	s += (ctx->data[ X01RequestIndexOffset1 ] << 0);
	return s;
}
uint16_t X01RequestGetCount(X01RequestContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X01RequestIndexCount0 ] << 8);
	s += (ctx->data[ X01RequestIndexCount1 ] << 0);
	return s;
}
uint16_t X01RequestCalcCrc(X01RequestContext* ctx)
{
	return CRC16(ctx->data, X01RequestIndexMax-2);
}
uint16_t X01RequestGetCrc(X01RequestContext* ctx)
{
	uint16_t crc = 0;
	crc += (ctx->data[ (X01RequestIndexCrc0) ] << 0);
	crc += (ctx->data[ (X01RequestIndexCrc1) ] << 8);
	return crc;
}
uint8_t X01RequestGetLength(X01RequestContext* ctx)
{
	return X01RequestIndexMax;
}
void X01RequestSetSlave(X01RequestContext* ctx, uint8_t c)
{
	ctx->data[ X01RequestIndexSlave ] = c;
}
void X01RequestSetFcode(X01RequestContext* ctx, uint8_t c)
{
	ctx->data[ X01RequestIndexFcode ] = c;
}
void X01RequestSetOffset(X01RequestContext* ctx, uint16_t s)
{
	ctx->data[ X01RequestIndexOffset0 ] = (s >> 8);
	ctx->data[ X01RequestIndexOffset1 ] = (s >> 0);
}
void X01RequestSetCount(X01RequestContext* ctx, uint16_t s)
{
	if( s < X01RequestCountMin )
	{
		s = X01RequestCountMin;
	}
	else if( s > X01RequestCountMax )
	{
		s = X01RequestCountMax;
	}
	ctx->data[ X01RequestIndexCount0 ] = (s >> 8);
	ctx->data[ X01RequestIndexCount1 ] = (s >> 0);
}
void X01RequestSetCrc(X01RequestContext* ctx, uint16_t crc)
{
	ctx->data[ (X01RequestIndexCrc0) ] = (crc >> 0);
	ctx->data[ (X01RequestIndexCrc1) ] = (crc >> 8);
}

void X01RequestShowContext(X01RequestContext* ctx)
{
	int i = 0;
	int len = X01RequestGetLength(ctx);

	printf("X01Request:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx->data[i]);
	}
	printf("\b].%s\n", X01RequestCheck(ctx) == 1 ? "ok" : "xxxx");
}

#ifdef TEST_X01REQUEST
int main(void)
{
	X01RequestContext ctx;

	X01RequestSetSlave(&ctx, 0x01);
	X01RequestSetFcode(&ctx, 0x01);
	X01RequestSetOffset(&ctx, 0x0001);
	X01RequestSetCount(&ctx, 0x0123);
	X01RequestSetCrc(&ctx, X01RequestCalcCrc(&ctx));

	X01RequestShowContext(&ctx);

	return 0;
}
#endif//TEST_X01REQUEST
