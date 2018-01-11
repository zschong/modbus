#include <stdio.h>
#include "modbuscrc16.h"
#include "x04response.h"

uint8_t X04ResponseCheck(X04ResponseContext* ctx)
{
	if( X04ResponseCalcCrc(ctx) != X04ResponseGetCrc(ctx) )
	{
		return 0;
	}
	if( X04ResponseGetBcount(ctx) < X04ResponseBcountMin )
	{
		return 0;
	}
	if( X04ResponseGetBcount(ctx) > X04ResponseBcountMax )
	{
		return 0;
	}
	return 1;
}
uint8_t X04ResponseGetSlave(X04ResponseContext* ctx)
{
	return ctx->data[ X04ResponseIndexSlave ];
}
uint8_t X04ResponseGetFcode(X04ResponseContext* ctx)
{
	return ctx->data[ X04ResponseIndexFcode ];
}
uint8_t X04ResponseGetBcount(X04ResponseContext* ctx)
{
	return ctx->data[ X04ResponseIndexBcount ];
}
uint16_t X04ResponseGetData(X04ResponseContext* ctx, uint8_t i)
{
	uint8_t index = (i * 2);

	if( index < X04ResponseBcountMin )
	{
		return 0;
	}
	else if( index > X04ResponseBcountMax )
	{
		return 0;
	}
	uint16_t data = 0;
	data += (ctx->data[ X04ResponseIndexData + (index + 0 - 2)] << 8);
	data += (ctx->data[ X04ResponseIndexData + (index + 1 - 2)] << 0);
	return data;
}
uint16_t X04ResponseCalcCrc(X04ResponseContext* ctx)
{
	return CRC16(ctx->data, (X04ResponseIndexData + X04ResponseGetBcount(ctx)));
}
uint16_t X04ResponseGetCrc(X04ResponseContext* ctx)
{
	uint16_t crc = 0;
	uint8_t len = X04ResponseGetLength(ctx);
	crc += (ctx->data[len - 1] << 8);
	crc += (ctx->data[len - 2] << 0);
	return crc;
}
uint8_t X04ResponseGetLength(X04ResponseContext* ctx)
{
	return (X04ResponseIndexData + X04ResponseGetBcount(ctx) + 2);
}
void X04ResponseSetSlave(X04ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X04ResponseIndexSlave ] = c;
}
void X04ResponseSetFcode(X04ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X04ResponseIndexFcode ] = c;
}
void X04ResponseSetBcount(X04ResponseContext* ctx, uint8_t c)
{
	ctx->data[ X04ResponseIndexBcount ] = c;
}
void X04ResponseSetData(X04ResponseContext* ctx, uint8_t i, uint16_t data)
{
	uint8_t index = (i * 2);

	if( index < X04ResponseBcountMin )
	{
		return;
	}
	else if( index > X04ResponseBcountMax )
	{
		return;
	}
	if( X04ResponseGetBcount(ctx) < index )
	{
		X04ResponseSetBcount(ctx, index);
	}
	ctx->data[ X04ResponseIndexData + (index + 0 - 2) ] = (uint8_t)(data >> 8);
	ctx->data[ X04ResponseIndexData + (index + 1 - 2) ] = (uint8_t)(data >> 0);
}
void X04ResponseSetCrc(X04ResponseContext* ctx, uint16_t crc)
{
	uint8_t len = X04ResponseGetLength(ctx);

	ctx->data[len - 1] = (crc >> 8);
	ctx->data[len - 2] = (crc >> 0);
}

void X04ResponseShowContext(X04ResponseContext* ctx)
{
	int i = 0;
	int len = X04ResponseGetLength(ctx);

	printf("X04Response:[");
	for(i = 0; i < len; i++)
	{
		printf("%02X ", ctx->data[i]);
	}
	printf("\b].%s\n", X04ResponseCheck(ctx) == 1 ? "ok" : "xxxx");
}

#ifdef TEST_X04RESPONSE
int main(void)
{
	X04ResponseContext ctx;

	X04ResponseSetSlave(&ctx, 0x01);
	X04ResponseSetFcode(&ctx, 0X04);
	X04ResponseSetBcount(&ctx, 0x02);
	X04ResponseSetData(&ctx, 1, 0x0017);
	X04ResponseSetCrc(&ctx, X04ResponseCalcCrc(&ctx));

	X04ResponseShowContext(&ctx);

	return 0;
}
#endif//TEST_X04RESPONSE
