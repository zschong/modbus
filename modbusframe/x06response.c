#include <stdio.h>
#include "modbuscrc16.h"
#include "x06response.h"

uint8_t X06ResponseCheck(X06ResponseContext* ctx)
{
	return (X06ResponseCalcCrc(ctx) == X06ResponseGetCrc(ctx)); 
}
uint8_t X06ResponseGetSlave(X06ResponseContext* ctx)
{
	return ctx->data[ X06ResponseIndexSlave ];
}
uint8_t X06ResponseGetFcode(X06ResponseContext* ctx)
{
	return ctx->data[ X06ResponseIndexFcode ];
}
uint16_t X06ResponseGetOffset(X06ResponseContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X06ResponseIndexOffset0 ] << 8);
	s += (ctx->data[ X06ResponseIndexOffset1 ] << 0);
	return s;
}
uint16_t X06ResponseGetValue(X06ResponseContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X06ResponseIndexValue0 ] << 8);
	s += (ctx->data[ X06ResponseIndexValue1 ] << 0);
	return s;
}
uint16_t X06ResponseCalcCrc(X06ResponseContext* ctx)
{
	return CRC16(ctx->data, X06ResponseIndexMax-2);
}
uint16_t X06ResponseGetCrc(X06ResponseContext* ctx)
{
	uint16_t crc = 0;
	crc += (ctx->data[ (X06ResponseIndexCrc0) ] << 0);
	crc += (ctx->data[ (X06ResponseIndexCrc1) ] << 8);
	return crc;
}
uint8_t X06ResponseGetLength(X06ResponseContext* ctx)
{
	return X06ResponseIndexMax;
}
void X06ResponseSetSlave(X06ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X06ResponseIndexSlave ] = c;
}
void X06ResponseSetFcode(X06ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X06ResponseIndexFcode ] = c;
}
void X06ResponseSetOffset(X06ResponseContext* ctx, uint16_t s)
{
	ctx->data[ X06ResponseIndexOffset0 ] = (s >> 8);
	ctx->data[ X06ResponseIndexOffset1 ] = (s >> 0);
}
void X06ResponseSetValue(X06ResponseContext* ctx, uint16_t s)
{
	ctx->data[ X06ResponseIndexValue0 ] = (s >> 8);
	ctx->data[ X06ResponseIndexValue1 ] = (s >> 0);
}
void X06ResponseSetCrc(X06ResponseContext* ctx, uint16_t crc)
{
	ctx->data[ (X06ResponseIndexCrc0) ] = (crc >> 0);
	ctx->data[ (X06ResponseIndexCrc1) ] = (crc >> 8);
}

void X06ResponseShowContext(X06ResponseContext* ctx)
{
	int i = 0;
	int len = X06ResponseGetLength(ctx);

	printf("X06Response:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx->data[i]);
	}
	printf("\b].%s\n", X06ResponseCheck(ctx) == 1 ? "ok" : "xxxx");
}

#ifdef TEST_X06RESPONSE
int main(void)
{
	X06ResponseContext ctx;

	X06ResponseSetSlave(&ctx, 0x01);
	X06ResponseSetFcode(&ctx, 0x06);
	X06ResponseSetOffset(&ctx, 0x0000);
	X06ResponseSetValue(&ctx, 0x3344);
	X06ResponseSetCrc(&ctx, X06ResponseCalcCrc(&ctx));

	X06ResponseShowContext(&ctx);

	return 0;
}
#endif//TEST_X06RESPONSE
