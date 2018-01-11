#include <stdio.h>
#include "modbuscrc16.h"
#include "x06request.h"

uint8_t X06RequestCheck(X06RequestContext* ctx)
{
	return (X06RequestCalcCrc(ctx) == X06RequestGetCrc(ctx)); 
}
uint8_t X06RequestGetSlave(X06RequestContext* ctx)
{
	return ctx->data[ X06RequestIndexSlave ];
}
uint8_t X06RequestGetFcode(X06RequestContext* ctx)
{
	return ctx->data[ X06RequestIndexFcode ];
}
uint16_t X06RequestGetOffset(X06RequestContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X06RequestIndexOffset0 ] << 8);
	s += (ctx->data[ X06RequestIndexOffset1 ] << 0);
	return s;
}
uint16_t X06RequestGetValue(X06RequestContext* ctx)
{
	uint16_t s = 0;
	s += (ctx->data[ X06RequestIndexValue0 ] << 8);
	s += (ctx->data[ X06RequestIndexValue1 ] << 0);
	return s;
}
uint16_t X06RequestCalcCrc(X06RequestContext* ctx)
{
	return CRC16(ctx->data, X06RequestIndexMax-2);
}
uint16_t X06RequestGetCrc(X06RequestContext* ctx)
{
	uint16_t crc = 0;
	crc += (ctx->data[ (X06RequestIndexCrc0) ] << 0);
	crc += (ctx->data[ (X06RequestIndexCrc1) ] << 8);
	return crc;
}
uint8_t X06RequestGetLength(X06RequestContext* ctx)
{
	return X06RequestIndexMax;
}
void X06RequestSetSlave(X06RequestContext* ctx, uint8_t c)
{
	ctx->data[ X06RequestIndexSlave ] = c;
}
void X06RequestSetFcode(X06RequestContext* ctx, uint8_t c)
{
	ctx->data[ X06RequestIndexFcode ] = c;
}
void X06RequestSetOffset(X06RequestContext* ctx, uint16_t s)
{
	ctx->data[ X06RequestIndexOffset0 ] = (s >> 8);
	ctx->data[ X06RequestIndexOffset1 ] = (s >> 0);
}
void X06RequestSetValue(X06RequestContext* ctx, uint16_t s)
{
	ctx->data[ X06RequestIndexValue0 ] = (s >> 8);
	ctx->data[ X06RequestIndexValue1 ] = (s >> 0);
}
void X06RequestSetCrc(X06RequestContext* ctx, uint16_t crc)
{
	ctx->data[ (X06RequestIndexCrc0) ] = (crc >> 0);
	ctx->data[ (X06RequestIndexCrc1) ] = (crc >> 8);
}

void X06RequestShowContext(X06RequestContext* ctx)
{
	int i = 0;
	int len = X06RequestGetLength(ctx);

	printf("X06Request:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx->data[i]);
	}
	printf("\b].%s\n", X06RequestCheck(ctx) == 1 ? "ok" : "xxxx");
}

#ifdef TEST_X06REQUEST
int main(void)
{
	X06RequestContext ctx;

	X06RequestSetSlave(&ctx, 0x01);
	X06RequestSetFcode(&ctx, 0x06);
	X06RequestSetOffset(&ctx, 0x0000);
	X06RequestSetValue(&ctx, 0x3344);
	X06RequestSetCrc(&ctx, X06RequestCalcCrc(&ctx));

	X06RequestShowContext(&ctx);

	return 0;
}
#endif//TEST_X06REQUEST
