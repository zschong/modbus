#include <stdio.h>
#include "modbuscrc16.h"
#include "x04request.h"

uint8_t X04RequestCheck(X04RequestContext* ctx)
{
	uint16_t count = X04RequestGetCount(ctx);

	if( X04RequestCalcCrc(ctx) != X04RequestGetCrc(ctx) )
	{
		return 0;
	}
	else if( count < X04RequestCountMin )
	{
		return 0;
	}
	else if( count > X04RequestCountMax )
	{
		return 0;
	}
	return 1;
}
uint8_t X04RequestGetSlave(X04RequestContext* ctx)
{
	return ctx->data[ X04RequestIndexSlave ];
}
uint8_t X04RequestGetFcode(X04RequestContext* ctx)
{
	return ctx->data[ X04RequestIndexFcode ];
}
uint16_t X04RequestGetOffset(X04RequestContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X04RequestIndexOffset0 ] << 8);
	s += (ctx->data[ X04RequestIndexOffset1 ] << 0);
	return s;
}
uint16_t X04RequestGetCount(X04RequestContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X04RequestIndexCount0 ] << 8);
	s += (ctx->data[ X04RequestIndexCount1 ] << 0);
	return s;
}
uint16_t X04RequestCalcCrc(X04RequestContext* ctx)
{
	return CRC16(ctx->data, X04RequestIndexMax-2);
}
uint16_t X04RequestGetCrc(X04RequestContext* ctx)
{
	uint16_t crc = 0;
	crc += (ctx->data[ (X04RequestIndexCrc0) ] << 0);
	crc += (ctx->data[ (X04RequestIndexCrc1) ] << 8);
	return crc;
}
uint8_t X04RequestGetLength(X04RequestContext* ctx)
{
	return X04RequestIndexMax;
}
void X04RequestSetSlave(X04RequestContext* ctx, uint8_t c)
{
	ctx->data[ X04RequestIndexSlave ] = c;
}
void X04RequestSetFcode(X04RequestContext* ctx, uint8_t c)
{
	ctx->data[ X04RequestIndexFcode ] = c;
}
void X04RequestSetOffset(X04RequestContext* ctx, uint16_t s)
{
	ctx->data[ X04RequestIndexOffset0 ] = (s >> 8);
	ctx->data[ X04RequestIndexOffset1 ] = (s >> 0);
}
void X04RequestSetCount(X04RequestContext* ctx, uint16_t s)
{
	if( s < X04RequestCountMin )
	{
		s = X04RequestCountMin;
	}
	else if( s > X04RequestCountMax )
	{
		s = X04RequestCountMax;
	}
	ctx->data[ X04RequestIndexCount0 ] = (s >> 8);
	ctx->data[ X04RequestIndexCount1 ] = (s >> 0);
}
void X04RequestSetCrc(X04RequestContext* ctx, uint16_t crc)
{
	ctx->data[ (X04RequestIndexCrc0) ] = (crc >> 0);
	ctx->data[ (X04RequestIndexCrc1) ] = (crc >> 8);
}

void X04RequestShowContext(X04RequestContext* ctx)
{
	int i = 0;
	int len = X04RequestGetLength(ctx);

	printf("X04Request:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx->data[i]);
	}
	printf("\b].%s\n", X04RequestCheck(ctx) == 1 ? "ok" : "xxxx");
}

#ifdef TEST_X04REQUEST
int main(void)
{
	X04RequestContext ctx;

	X04RequestSetSlave(&ctx, 0x01);
	X04RequestSetFcode(&ctx, 0x04);
	X04RequestSetOffset(&ctx, 0x0001);
	X04RequestSetCount(&ctx, 0x0001);
	X04RequestSetCrc(&ctx, X04RequestCalcCrc(&ctx));

	X04RequestShowContext(&ctx);

	return 0;
}
#endif//TEST_X04REQUEST
