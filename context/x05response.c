#include <stdio.h>
#include "modbuscrc16.h"
#include "x05response.h"

uint8_t X05ResponseCheck(X05ResponseContext* ctx)
{
	if( X05ResponseCalcCrc(ctx) != X05ResponseGetCrc(ctx) )
	{
		return 0;
	}
	switch( X05ResponseGetValue(ctx) )
	{
		case X05ResponseValueOn:
		case X05ResponseValueOff:
			return 1;
	}
	return 0;
}
uint8_t X05ResponseGetSlave(X05ResponseContext* ctx)
{
	return ctx->data[ X05ResponseIndexSlave ];
}
uint8_t X05ResponseGetFcode(X05ResponseContext* ctx)
{
	return ctx->data[ X05ResponseIndexFcode ];
}
uint16_t X05ResponseGetOffset(X05ResponseContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X05ResponseIndexOffset0 ] << 8);
	s += (ctx->data[ X05ResponseIndexOffset1 ] << 0);
	return s;
}
uint16_t X05ResponseGetValue(X05ResponseContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X05ResponseIndexValue0 ] << 8);
	s += (ctx->data[ X05ResponseIndexValue1 ] << 0);
	return s;
}
uint16_t X05ResponseCalcCrc(X05ResponseContext* ctx)
{
	return CRC16(ctx->data, X05ResponseIndexMax-2);
}
uint16_t X05ResponseGetCrc(X05ResponseContext* ctx)
{
	uint16_t crc = 0;
	crc += (ctx->data[ (X05ResponseIndexCrc0) ] << 0);
	crc += (ctx->data[ (X05ResponseIndexCrc1) ] << 8);
	return crc;
}
uint8_t X05ResponseGetLength(X05ResponseContext* ctx)
{
	return X05ResponseIndexMax;
}
void X05ResponseSetSlave(X05ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X05ResponseIndexSlave ] = c;
}
void X05ResponseSetFcode(X05ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X05ResponseIndexFcode ] = c;
}
void X05ResponseSetOffset(X05ResponseContext* ctx, uint16_t s)
{
	ctx->data[ X05ResponseIndexOffset0 ] = (s >> 8);
	ctx->data[ X05ResponseIndexOffset1 ] = (s >> 0);
}
void X05ResponseSetValue(X05ResponseContext* ctx, uint16_t s)
{
	if( X05ResponseValueOff != s )
	{
		s = X05ResponseValueOn;
	}
	ctx->data[ X05ResponseIndexValue0 ] = (s >> 8);
	ctx->data[ X05ResponseIndexValue1 ] = (s >> 0);
}
void X05ResponseSetCrc(X05ResponseContext* ctx, uint16_t crc)
{
	ctx->data[ (X05ResponseIndexCrc0) ] = (crc >> 0);
	ctx->data[ (X05ResponseIndexCrc1) ] = (crc >> 8);
}

void X05ResponseShowContext(X05ResponseContext* ctx)
{
	int i = 0;
	int len = X05ResponseGetLength(ctx);

	printf("X05Response:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx->data[i]);
	}
	printf("\b].%s\n", X05ResponseCheck(ctx) == 1 ? "ok" : "xxxx");
}

#ifdef TEST_X05RESPONSE
int main(void)
{
	X05ResponseContext ctx;

	X05ResponseSetSlave(&ctx, 0x01);
	X05ResponseSetFcode(&ctx, 0x05);
	X05ResponseSetOffset(&ctx, 0x0000);
	X05ResponseSetValue(&ctx, X05ResponseValueOn);
	X05ResponseSetCrc(&ctx, X05ResponseCalcCrc(&ctx));

	X05ResponseShowContext(&ctx);

	return 0;
}
#endif//TEST_X05RESPONSE
