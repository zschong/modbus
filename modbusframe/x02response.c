#include <stdio.h>
#include <string.h>
#include "modbuscrc16.h"
#include "x02response.h"

uint8_t X02ResponseCheck(X02ResponseContext* ctx)
{
	if( X02ResponseCalcCrc(ctx) != X02ResponseGetCrc(ctx) )
	{
		return 0;
	}
	if( X02ResponseGetBcount(ctx) > X02ResponseBcountMax )
	{
		return 0;
	}
	return 1;
}
uint8_t X02ResponseGetSlave(X02ResponseContext* ctx)
{
	return ctx->data[ X02ResponseIndexSlave ];
}
uint8_t X02ResponseGetFcode(X02ResponseContext* ctx)
{
	return ctx->data[ X02ResponseIndexFcode ];
}
uint8_t X02ResponseGetBcount(X02ResponseContext* ctx)
{
	return ctx->data[ X02ResponseIndexBcount ];
}
uint8_t X02ResponseGetCoil(X02ResponseContext* ctx, uint16_t i)
{
	uint8_t index = (i / 8) + 1;

	if( index > X02ResponseBcountMax )
	{
		return 0;
	}
	return (ctx->data[ (X02ResponseIndexData + index -1) ] >> (i % 8)) & 0x01;
}
uint16_t X02ResponseCalcCrc(X02ResponseContext* ctx)
{
	return CRC16(ctx->data, (X02ResponseIndexData + X02ResponseGetBcount(ctx)));
}
uint16_t X02ResponseGetCrc(X02ResponseContext* ctx)
{
	uint16_t crc = 0;
	uint8_t len = X02ResponseGetLength(ctx);
	crc += (ctx->data[len - 1] << 8);
	crc += (ctx->data[len - 2] << 0);
	return crc;
}
uint8_t X02ResponseGetLength(X02ResponseContext* ctx)
{
	return (X02ResponseIndexData + X02ResponseGetBcount(ctx) + 2);
}
void X02ResponseSetSlave(X02ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X02ResponseIndexSlave ] = c;
}
void X02ResponseSetFcode(X02ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X02ResponseIndexFcode ] = c;
}
void X02ResponseSetBcount(X02ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X02ResponseIndexBcount ] = c;
}
void X02ResponseSetCoil(X02ResponseContext* ctx, uint16_t i, uint8_t status)
{
	uint8_t bit = (i % 8);
	uint8_t byte = (i / 8);

	if( i < X02RequestCountMin )
	{
		return;
	}
	if( i > X02RequestCountMax )
	{
		return;
	}
	if( (byte + 1) > X02ResponseBcountMax )
	{
		return;
	}
	if( X02ResponseGetBcount(ctx) < (byte + 1) )
	{
		X02ResponseSetBcount(ctx, (byte + 1));
	}
	if( 0 == status )
	{
		ctx->data[ (X02ResponseIndexData + byte) ] &= ~(1 << bit);
	}
	else
	{
		ctx->data[ (X02ResponseIndexData + byte) ] |= (1 << bit);
	}
}
void X02ResponseSetCrc(X02ResponseContext* ctx, uint16_t crc)
{
	uint8_t len = X02ResponseGetLength(ctx);

	ctx->data[len - 1] = (crc >> 8);
	ctx->data[len - 2] = (crc >> 0);
}

void X02ResponseShowContext(X02ResponseContext* ctx)
{
	int i = 0;
	int len = X02ResponseGetLength(ctx);

	printf("X02Response:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx->data[i]);
	}
	printf("\b].%s\n", X02ResponseCheck(ctx) == 1 ? "ok" : "xxxx");
}

#ifdef TEST_X02RESPONSE
int main(void)
{
	X02ResponseContext ctx;

	memset(ctx.data, 0, sizeof(ctx.data));
	X02ResponseSetSlave(&ctx, 0x01);
	X02ResponseSetFcode(&ctx, 0X02);
	X02ResponseSetBcount(&ctx, 0x01);
	for(int i = 0; i < 100; i++)
	{
		X02ResponseSetCoil(&ctx, i, i%3 && i&1);
	}
	X02ResponseSetCrc(&ctx, X02ResponseCalcCrc(&ctx));

	X02ResponseShowContext(&ctx);

	return 0;
}
#endif//TEST_X02RESPONSE
