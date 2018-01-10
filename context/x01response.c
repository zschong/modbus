#include <stdio.h>
#include <string.h>
#include "modbuscrc16.h"
#include "x01response.h"

uint8_t X01ResponseCheck(X01ResponseContext* ctx)
{
	if( X01ResponseCalcCrc(ctx) != X01ResponseGetCrc(ctx) )
	{
		return 0;
	}
	if( X01ResponseGetBcount(ctx) < X01ResponseBcountMin )
	{
		return 0;
	}
	else if( X01ResponseGetBcount(ctx) > X01ResponseBcountMax )
	{
		return 0;
	}
	return 1;
}
uint8_t X01ResponseGetSlave(X01ResponseContext* ctx)
{
	return ctx->data[ X01ResponseIndexSlave ];
}
uint8_t X01ResponseGetFcode(X01ResponseContext* ctx)
{
	return ctx->data[ X01ResponseIndexFcode ];
}
uint8_t X01ResponseGetBcount(X01ResponseContext* ctx)
{
	return ctx->data[ X01ResponseIndexBcount ];
}
uint8_t X01ResponseGetCoil(X01ResponseContext* ctx, uint16_t i)
{
	uint8_t index = (i / 8) + 1;

	if( index > X01ResponseBcountMax )
	{
		return 0;
	}
	return (ctx->data[ (X01ResponseIndexData + index -1) ] >> (i % 8)) & 0x01;
}
uint16_t X01ResponseCalcCrc(X01ResponseContext* ctx)
{
	return CRC16(ctx->data, (X01ResponseIndexData + X01ResponseGetBcount(ctx)));
}
uint16_t X01ResponseGetCrc(X01ResponseContext* ctx)
{
	uint16_t crc = 0;
	uint8_t len = X01ResponseGetLength(ctx);
	crc += (ctx->data[len - 1] << 8);
	crc += (ctx->data[len - 2] << 0);
	return crc;
}
uint8_t X01ResponseGetLength(X01ResponseContext* ctx)
{
	return (X01ResponseIndexData + X01ResponseGetBcount(ctx) + 2);
}
void X01ResponseSetSlave(X01ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X01ResponseIndexSlave ] = c;
}
void X01ResponseSetFcode(X01ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X01ResponseIndexFcode ] = c;
}
void X01ResponseSetBcount(X01ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X01ResponseIndexBcount ] = c;
}
void X01ResponseSetCoil(X01ResponseContext* ctx, uint16_t i, uint8_t status)
{
	uint8_t index = (i / 8) + !!(i % 8);

	if( index < X01ResponseBcountMin )
	{
		return;
	}
	else if( index > X01ResponseBcountMax )
	{
		return;
	}
	if( X01ResponseGetBcount(ctx) < index )
	{
		X01ResponseSetBcount(ctx, index);
	}
	ctx->data[ (X01ResponseIndexData + index -1) ] |= (!!status) << (i % 8);
}
void X01ResponseSetCrc(X01ResponseContext* ctx, uint16_t crc)
{
	uint8_t len = X01ResponseGetLength(ctx);

	ctx->data[len - 1] = (crc >> 8);
	ctx->data[len - 2] = (crc >> 0);
}

void X01ResponseShowContext(X01ResponseContext* ctx)
{
	int i = 0;
	int len = X01ResponseGetLength(ctx);

	printf("X01Response:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx->data[i]);
	}
	printf("\b].%s\n", X01ResponseCheck(ctx) == 1 ? "ok" : "xxxx");
}

#ifdef TEST_X01RESPONSE
int main(void)
{
	X01ResponseContext ctx;

	memset(ctx.data, 0, sizeof(ctx.data));
	X01ResponseSetSlave(&ctx, 0x01);
	X01ResponseSetFcode(&ctx, 0X01);
	X01ResponseSetBcount(&ctx, 0x01);
	for(int i = 0; i < 100; i++)
	{
		X01ResponseSetCoil(&ctx, i, i%3 && i&1);
	}
	X01ResponseSetCrc(&ctx, X01ResponseCalcCrc(&ctx));

	X01ResponseShowContext(&ctx);

	return 0;
}
#endif//TEST_X01RESPONSE
