#include <stdio.h>
#include "modbuscrc16.h"
#include "x0frequest.h"

uint8_t X0fRequestCheck(X0fRequestContext* ctx)
{
	const uint16_t count = X0fRequestGetCount(ctx);
	const uint8_t bcount = X0fRequestGetBcount(ctx);

	if( X0fRequestCalcCrc(ctx) != X0fRequestGetCrc(ctx) )
	{
		return 0;
	}
	else if( count < X0fRequestCountMin )
	{
		return 0;
	}
	else if( count > X0fRequestCountMax )
	{
		return 0;
	}
	return ((count / 8) + !!(count % 8)) == bcount;
}
uint8_t X0fRequestGetSlave(X0fRequestContext* ctx)
{
	return ctx->data[ X0fRequestIndexSlave ];
}
uint8_t X0fRequestGetFcode(X0fRequestContext* ctx)
{
	return ctx->data[ X0fRequestIndexFcode ];
}
uint16_t X0fRequestGetOffset(X0fRequestContext* ctx)
{
	uint16_t offset = 0;
	offset += (ctx->data[ X0fRequestIndexOffset0 ] << 8);
	offset += (ctx->data[ X0fRequestIndexOffset1 ] << 0);
	return offset;
}
uint16_t X0fRequestGetCount(X0fRequestContext* ctx)
{
	uint16_t count = 0;
	count += (ctx->data[ X0fRequestIndexCount0 ] << 8);
	count += (ctx->data[ X0fRequestIndexCount1 ] << 0);
	return count;
}
uint8_t  X0fRequestGetBcount(X0fRequestContext* ctx)
{
	return ctx->data[ X0fRequestIndexBcount ];
}
uint16_t X0fRequestGetCoil(X0fRequestContext* ctx, uint16_t i)
{
	uint8_t bit = (i % 8);
	uint8_t byte = (i / 8);

	if( i >= X0fRequestCountMax )
	{
		return 0;
	}
	if( i >= X0fRequestGetCount(ctx) )
	{
		return 0;
	}
	return ctx->data[ (X0fRequestIndexData + byte) ] & (1 << bit);
}
uint16_t X0fRequestCalcCrc(X0fRequestContext* ctx)
{
	return CRC16(ctx->data, X0fRequestIndexData + X0fRequestGetBcount(ctx));
}
uint16_t X0fRequestGetCrc(X0fRequestContext* ctx)
{
	uint16_t crc = 0;
	uint16_t len = X0fRequestGetBcount(ctx);

	crc += (ctx->data[ (X0fRequestIndexData + len + 0) ] << 0);
	crc += (ctx->data[ (X0fRequestIndexData + len + 1) ] << 8);

	return crc;
}
uint8_t X0fRequestGetLength(X0fRequestContext* ctx)
{
	return X0fRequestIndexData + X0fRequestGetBcount(ctx) + 2;
}

void X0fRequestSetSlave(X0fRequestContext* ctx, uint8_t c)
{
	ctx->data[ X0fRequestIndexSlave ] = c;
}
void X0fRequestSetFcode(X0fRequestContext* ctx, uint8_t c)
{
	ctx->data[ X0fRequestIndexFcode ] = c;
}
void X0fRequestSetOffset(X0fRequestContext* ctx, uint16_t s)
{
	ctx->data[ X0fRequestIndexOffset0 ] = (s >> 8);
	ctx->data[ X0fRequestIndexOffset1 ] = (s >> 0);
}
void X0fRequestSetCount(X0fRequestContext* ctx, uint16_t s)
{
	ctx->data[ X0fRequestIndexCount0 ] = (s >> 8);
	ctx->data[ X0fRequestIndexCount1 ] = (s >> 0);
}
void X0fRequestSetBcount(X0fRequestContext* ctx, uint8_t c)
{
	ctx->data[ X0fRequestIndexBcount ] = c;
}
void X0fRequestSetCoil(X0fRequestContext* ctx, uint16_t i, uint8_t status)
{
	uint8_t bit = (i % 8);
	uint8_t byte = (i / 8);

	if( i >= X0fRequestCountMax )
	{
		return;
	}
	if( (byte + 1) > X0fRequestGetBcount(ctx) )
	{
		X0fRequestSetBcount(ctx, byte + 1);
	}
	if( 0 == status )
	{
		ctx->data[ (X0fRequestIndexData + byte) ] &= ~((uint8_t)(1 << bit));
	}
	else
	{
		ctx->data[ (X0fRequestIndexData + byte) ] |= (uint8_t)(1 << bit);
	}
}
void X0fRequestSetCrc(X0fRequestContext* ctx, uint16_t s)
{
	uint8_t len = X0fRequestGetBcount(ctx);

	ctx->data[ (X0fRequestIndexData + len + 0) ] = (s >> 0);
	ctx->data[ (X0fRequestIndexData + len + 1) ] = (s >> 8);
}

void X0fRequestShowContext(X0fRequestContext* ctx)
{
	uint8_t i = 0;
	uint8_t len = X0fRequestGetLength(ctx);

	printf("X0fRequest:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx->data[i]);
	}
	printf("\b].%s\n", X0fRequestCheck(ctx) == 1 ? "ok" : "xxxx");
}

#ifdef TEST_X0fREQUEST
int main(void)
{
	X0fRequestContext ctx;

	X0fRequestSetSlave(&ctx, 0x01);
	X0fRequestSetFcode(&ctx, 0x0f);
	X0fRequestSetOffset(&ctx, 0x0000);
	X0fRequestSetCount(&ctx, 0x0020);
	for(uint16_t i = 0; i < 0x20; i++)
	{
		X0fRequestSetCoil(&ctx, i, i%3);
	}
	X0fRequestSetCrc(&ctx, X0fRequestCalcCrc(&ctx));

	X0fRequestShowContext(&ctx);

	return 0;
}
#endif//TEST_X0fREQUEST
