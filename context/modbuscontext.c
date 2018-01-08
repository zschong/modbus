#include <stdio.h>
#include <string.h>
#include "modbuscontext.h"


void MBContextInit(MBContext* m)
{
	m->mac = 0;
	m->index = 0;
}
void MBContextPush(MBContext* m, uint8_t c)
{
	if( m->index < sizeof(m->buffer) )
	{
		m->buffer[ m->index++ ] = c;
	}
}
void MBContextSetMac(MBContext *m, uint8_t c)
{
	m->mac = c;
}
uint8_t MBContextCheckX03Request(MBContext* m)
{
	if( m->index < X03RequestIndexMax )
	{
		return 0;
	}
	if( X03RequestCheck( (X03RequestContext*)m->buffer ) == 0 )
	{
		m->index--;
		memmove(m->buffer, m->buffer + 1, m->index);
		return 0;
	}
	return 1;
}
uint8_t MBContextCheckX03Response(MBContext* m)
{
	if( m->index < X03ResponseIndexData )
	{
		return 0;
	}
	uint8_t bcount = X03ResponseGetBcount( (X03ResponseContext*)m->buffer );
	if( bcount < X03ResponseBcountMin || bcount > X03ResponseBcountMax )
	{
		m->index--;
		memmove(m->buffer, m->buffer + 1, m->index);
		return 0;
	}
	if( m->index < (X03ResponseIndexData + bcount + 2) )
	{
		return 0;
	}
	if( X03ResponseCheck( (X03ResponseContext*)m->buffer ) == 0 )
	{
		m->index--;
		memmove(m->buffer, m->buffer + 1, m->index);
		return 0;
	}
	return 1;
}
uint8_t MBContextCheckX10Request(MBContext* m)
{
	if( m->index < X10RequestIndexData )
	{
		return 0;
	}
	uint8_t count = X10RequestGetCount( (X10RequestContext*)m->buffer );
	if( count < X10RequestCountMin || count > X10RequestCountMax )
	{
		m->index--;
		memmove(m->buffer, m->buffer + 1, m->index);
		return 0;
	}
	uint8_t bcount = X10RequestGetBcount( (X10RequestContext*)m->buffer );
	if( (count * 2) != bcount )
	{
		m->index--;
		memmove(m->buffer, m->buffer + 1, m->index);
		return 0;
	}
	if( m->index < (X10RequestIndexData + bcount + 2) )
	{
		return 0;
	}
	if( X10RequestCheck( (X10RequestContext*)m->buffer ) == 0 )
	{
		m->index--;
		memmove(m->buffer, m->buffer + 1, m->index);
		return 0;
	}
	return 1;
}
uint8_t MBContextCheckX10Response(MBContext* m)
{
	if( m->index < X10ResponseIndexMax )
	{
		return 0;
	}
	uint8_t count = X10ResponseGetCount( (X10ResponseContext*)m->buffer );
	if( count < X10ResponseCountMin || count > X10ResponseCountMax )
	{
		m->index--;
		memmove(m->buffer, m->buffer + 1, m->index);
		return 0;
	}
	if( X10ResponseCheck( (X10ResponseContext*)m->buffer ) == 0 )
	{
		m->index--;
		memmove(m->buffer, m->buffer + 1, m->index);
		return 0;
	}
	return 1;
}
uint8_t MBContextCheckRequest(MBContext* m)
{
	if( m->index < 2)
	{
		return 0;
	}
	if( m->mac != m->buffer[ MBContextIndexSlave ] )
	{
		m->index--;
		memmove(m->buffer, m->buffer + 1, m->index);
		return 0;
	}
	switch( m->buffer[ MBContextIndexFcode ] )
	{
		case MBContextFcodeX03:
			return MBContextCheckX03Request(m);

		case MBContextFcodeX10:
			return MBContextCheckX10Request(m);
	}
	m->index--;
	memmove(m->buffer, m->buffer + 1, m->index);
	return 0;
}
uint8_t MBContextCheckResponse(MBContext* m)
{
	if( m->index < 2)
	{
		return 0;
	}
	if( m->mac != m->buffer[ MBContextIndexSlave ] )
	{
		m->index--;
		memmove(m->buffer, m->buffer + 1, m->index);
		return 0;
	}
	switch( m->buffer[ MBContextIndexFcode ] )
	{
		case MBContextFcodeX03:
			return MBContextCheckX03Response(m);

		case MBContextFcodeX10:
			return MBContextCheckX10Response(m);
	}
	m->index--;
	memmove(m->buffer, m->buffer + 1, m->index);
	return 0;
}
X03RequestContext* MBContextGetX03RequestContext(MBContext* m)
{
	return (X03RequestContext*)m->buffer;
}
X03ResponseContext* MBContextGetX03ResponseContext(MBContext* m)
{
	return (X03ResponseContext*)m->buffer;
}
X10RequestContext* MBContextGetX10RequestContext(MBContext* m)
{
	return (X10RequestContext*)m->buffer;
}
X10ResponseContext* MBContextGetX10ResponseContext(MBContext* m)
{
	return (X10ResponseContext*)m->buffer;
}
uint8_t MBContextGetLength(MBContext* m)
{
	return m->index;
}
uint8_t MBContextGetFcode(MBContext* m)
{
	return m->buffer[ MBContextIndexFcode ];
}

#ifdef TEST_CONTEXT
int CheckRequest(uint8_t mac, uint8_t *data, int len)
{
	int i = 0;
	MBContext context;

	MBContextInit(&context);
	MBContextSetMac(&context, mac);

	for(i = 0; data && i < len; i++)
	{
		MBContextPush(&context, data[i]);
		if( MBContextCheckRequest(&context) == 1 )
		{
			i++;
			printf("%s (%3u,%3u)=%2u\n", 
					__func__, (i - context.index), i, context.index);
			break;
		}
	}
	return i;
}
int CheckResponse(uint8_t mac, uint8_t *data, int len)
{
	int i = 0;
	MBContext context;

	MBContextInit(&context);
	MBContextSetMac(&context, mac);

	for(i = 0; data && i < len; i++)
	{
		MBContextPush(&context, data[i]);
		if( MBContextCheckResponse(&context) == 1 )
		{
			i++;
			printf("%s(%#3u,%3u)=%2u\n", 
					__func__, (i - context.index), i, context.index);
			break;
		}
	}
	return i;
}
void TestX03Request(X03RequestContext* x)
{
	X03RequestSetSlave(x, 0x01);
	X03RequestSetFcode(x, 0x03);
	X03RequestSetOffset(x, 0x0004);
	X03RequestSetCount(x, 0x0005);
	X03RequestSetCrc(x, X03RequestCalcCrc(x));
	X03RequestShowContext(x);
}
void TestX03Response(X03ResponseContext* x)
{
	X03ResponseSetSlave(x, 0x02);
	X03ResponseSetFcode(x, 0x03);
	X03ResponseSetBcount(x, 0x04);
	X03ResponseSetData(x, 1, 0xABCD);
	X03ResponseSetData(x, 2, 0x3456);
	X03ResponseSetCrc(x, X03ResponseCalcCrc(x));
	X03ResponseShowContext(x);
}
void TestX10Request(X10RequestContext* x)
{
	X10RequestSetSlave(x, 0x01);
	X10RequestSetFcode(x, 0x10);
	X10RequestSetOffset(x, 0x1234);
	X10RequestSetCount(x, 0x0008);
	X10RequestSetBcount(x, 0x0010);
	X10RequestSetData(x, 1, 0x5678);
	X10RequestSetData(x, 2, 0x9ABC);
	X10RequestSetData(x, 3, 0x6C40);
	X10RequestSetData(x, 4, 0x7A50);
	X10RequestSetData(x, 5, 0x8830);
	X10RequestSetData(x, 6, 0x9290);
	X10RequestSetData(x, 7, 0xA05A);
	X10RequestSetData(x, 8, 0xB281);
	X10RequestSetCrc(x, X10RequestCalcCrc(x));
	X10RequestShowContext(x);
}
void TestX10Response(X10ResponseContext* x)
{
	X10ResponseSetSlave(x, 0x03);
	X10ResponseSetFcode(x, 0x10);
	X10ResponseSetOffset(x, 0x1234);
	X10ResponseSetCount(x, 0x0003);
	X10ResponseSetCrc(x, X10ResponseCalcCrc(x));
	X10ResponseShowContext(x);
}
int main(void)
{
	X03RequestContext x03request;
	X03ResponseContext x03response;
	X10RequestContext x10request;
	X10ResponseContext x10response;

	TestX03Request(&x03request);
	TestX03Response(&x03response);
	TestX10Request(&x10request);
	TestX10Response(&x10response);

	int i = 0;
	uint8_t buf[256];

	memcpy(buf + 11, x03request.data, X03RequestGetLength(&x03request));
	memcpy(buf + 33, x03response.data, X03ResponseGetLength(&x03response));
	memcpy(buf + 55, x10request.data, X10RequestGetLength(&x10request));
	memcpy(buf + 77, x10response.data, X10ResponseGetLength(&x10response));
	CheckRequest (0x01, buf, sizeof(buf));
	CheckResponse(0x02, buf, sizeof(buf));
	CheckRequest (0x01, buf, sizeof(buf));
	CheckResponse(0x03, buf, sizeof(buf));

	return 0;
}
#endif//TEST_CONTEXT
