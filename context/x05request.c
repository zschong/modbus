#include <stdio.h>
#include "modbuscrc16.h"
#include "x05request.h"

uint8_t X05RequestCheck(X05RequestContext* ctx)
{
	if( X05RequestCalcCrc(ctx) != X05RequestGetCrc(ctx) )
	{
		return 0;
	}
	switch( X05RequestGetValue(ctx) )
	{
		case X05RequestValueOn:
		case X05RequestValueOff:
			return 1;
	}
	return 0;
}
uint8_t X05RequestGetSlave(X05RequestContext* ctx)
{
	return ctx->data[ X05RequestIndexSlave ];
}
uint8_t X05RequestGetFcode(X05RequestContext* ctx)
{
	return ctx->data[ X05RequestIndexFcode ];
}
uint16_t X05RequestGetOffset(X05RequestContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X05RequestIndexOffset0 ] << 8);
	s += (ctx->data[ X05RequestIndexOffset1 ] << 0);
	return s;
}
uint16_t X05RequestGetValue(X05RequestContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X05RequestIndexValue0 ] << 8);
	s += (ctx->data[ X05RequestIndexValue1 ] << 0);
	return s;
}
uint16_t X05RequestCalcCrc(X05RequestContext* ctx)
{
	return CRC16(ctx->data, X05RequestIndexMax-2);
}
uint16_t X05RequestGetCrc(X05RequestContext* ctx)
{
	uint16_t crc = 0;
	crc += (ctx->data[ (X05RequestIndexCrc0) ] << 0);
	crc += (ctx->data[ (X05RequestIndexCrc1) ] << 8);
	return crc;
}
uint8_t X05RequestGetLength(X05RequestContext* ctx)
{
	return X05RequestIndexMax;
}
void X05RequestSetSlave(X05RequestContext* ctx, uint8_t c)
{
	ctx->data[ X05RequestIndexSlave ] = c;
}
void X05RequestSetFcode(X05RequestContext* ctx, uint8_t c)
{
	ctx->data[ X05RequestIndexFcode ] = c;
}
void X05RequestSetOffset(X05RequestContext* ctx, uint16_t s)
{
	ctx->data[ X05RequestIndexOffset0 ] = (s >> 8);
	ctx->data[ X05RequestIndexOffset1 ] = (s >> 0);
}
void X05RequestSetValue(X05RequestContext* ctx, uint16_t s)
{
	if( X05RequestValueOff != s )
	{
		s = X05RequestValueOn;
	}
	ctx->data[ X05RequestIndexValue0 ] = (s >> 8);
	ctx->data[ X05RequestIndexValue1 ] = (s >> 0);
}
void X05RequestSetCrc(X05RequestContext* ctx, uint16_t crc)
{
	ctx->data[ (X05RequestIndexCrc0) ] = (crc >> 0);
	ctx->data[ (X05RequestIndexCrc1) ] = (crc >> 8);
}

void X05RequestShowContext(X05RequestContext* ctx)
{
	int i = 0;
	int len = X05RequestGetLength(ctx);

	printf("X05Request:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx->data[i]);
	}
	printf("\b].%s\n", X05RequestCheck(ctx) == 1 ? "ok" : "xxxx");
}

#ifdef TEST_X05REQUEST
int main(void)
{
	X05RequestContext ctx;

	X05RequestSetSlave(&ctx, 0x01);
	X05RequestSetFcode(&ctx, 0x05);
	X05RequestSetOffset(&ctx, 0x0000);
	X05RequestSetValue(&ctx, X05RequestValueOn);
	X05RequestSetCrc(&ctx, X05RequestCalcCrc(&ctx));

	X05RequestShowContext(&ctx);

	return 0;
}
#endif//TEST_X05REQUEST
