#include <stdio.h>
#include "modbuscrc16.h"
#include "x0fresponse.h"

uint8_t X0fResponseCheck(X0fResponseContext* ctx)
{
	const uint16_t count = X0fResponseGetCount(ctx);

	if( X0fResponseCalcCrc(ctx) != X0fResponseGetCrc(ctx) )
	{
		return 0;
	}
	else if( count < X0fResponseCountMin )
	{
		return 0;
	}
	else if( count > X0fResponseCountMax )
	{
		return 0;
	}
	return 1;
}
uint8_t X0fResponseGetSlave(X0fResponseContext* ctx)
{
	return ctx->data[ X0fResponseIndexSlave ];
}
uint8_t X0fResponseGetFcode(X0fResponseContext* ctx)
{
	return ctx->data[ X0fResponseIndexFcode ];
}
uint16_t X0fResponseGetOffset(X0fResponseContext* ctx)
{
	uint16_t offset = 0;
	offset += (ctx->data[ X0fResponseIndexOffset0 ] << 8);
	offset += (ctx->data[ X0fResponseIndexOffset1 ] << 0);
	return offset;
}
uint16_t X0fResponseGetCount(X0fResponseContext* ctx)
{
	uint16_t count = 0;
	count += (ctx->data[ X0fResponseIndexCount0 ] << 8);
	count += (ctx->data[ X0fResponseIndexCount1 ] << 0);
	return count;
}
uint16_t X0fResponseCalcCrc(X0fResponseContext* ctx)
{
	return CRC16(ctx->data, X0fResponseIndexMax - 2);
}
uint16_t X0fResponseGetCrc(X0fResponseContext* ctx)
{
	uint16_t crc = 0;

	crc += (ctx->data[ (X0fResponseIndexMax - 2) ] << 0);
	crc += (ctx->data[ (X0fResponseIndexMax - 1) ] << 8);

	return crc;
}
uint8_t X0fResponseGetLength(X0fResponseContext* ctx)
{
	return X0fResponseIndexMax;
}

void X0fResponseSetSlave(X0fResponseContext* ctx, uint8_t c)
{
	ctx->data[ X0fResponseIndexSlave ] = c;
}
void X0fResponseSetFcode(X0fResponseContext* ctx, uint8_t c)
{
	ctx->data[ X0fResponseIndexFcode ] = c;
}
void X0fResponseSetOffset(X0fResponseContext* ctx, uint16_t s)
{
	ctx->data[ X0fResponseIndexOffset0 ] = (s >> 8);
	ctx->data[ X0fResponseIndexOffset1 ] = (s >> 0);
}
void X0fResponseSetCount(X0fResponseContext* ctx, uint16_t s)
{
	ctx->data[ X0fResponseIndexCount0 ] = (s >> 8);
	ctx->data[ X0fResponseIndexCount1 ] = (s >> 0);
}
void X0fResponseSetCrc(X0fResponseContext* ctx, uint16_t s)
{
	ctx->data[ (X0fResponseIndexMax - 2) ] = (s >> 0);
	ctx->data[ (X0fResponseIndexMax - 1) ] = (s >> 8);
}

void X0fResponseShowContext(X0fResponseContext* ctx)
{
	uint8_t i = 0;
	uint8_t len = X0fResponseGetLength(ctx);

	printf("X0fResponse:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx->data[i]);
	}
	printf("\b].%s\n", X0fResponseCheck(ctx) == 1 ? "ok" : "xxxx");
}

#ifdef TEST_X0fRESPONSE
int main(void)
{
	X0fResponseContext ctx;

	X0fResponseSetSlave(&ctx, 0x01);
	X0fResponseSetFcode(&ctx, 0x0f);
	X0fResponseSetOffset(&ctx, 0x0100);
	X0fResponseSetCount(&ctx, 0x0020);
	X0fResponseSetCrc(&ctx, X0fResponseCalcCrc(&ctx));

	X0fResponseShowContext(&ctx);

	return 0;
}
#endif//TEST_X0fRESPONSE
