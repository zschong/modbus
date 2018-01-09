#include <stdio.h>
#include "mcontext.h"

Mcontext::Mcontext(void)
{
	Init();
}
void Mcontext::Init(void)
{
	MBContextInit(&context);
}
void Mcontext::SetMaster(uint8_t master)
{
	MBContextSetMaster(&context, master);
}
void Mcontext::Show(void)
{
	printf("[");
	for(int i = 0; i < GetLength(); i++)
	{
		printf("%02X ", context.buffer[i]);
	}
	printf("\b]\n");
}
void Mcontext::Push(uint8_t c)	
{
	MBContextPush(&context, c);
}
void Mcontext::PushW(uint16_t w)
{
	MBContextPush(&context, (w >> 8));
	MBContextPush(&context, (w >> 0));
}
bool Mcontext::CheckRequest(void)
{
	return MBContextCheckRequest(&context);
}
bool Mcontext::CheckResponse(void)
{
	return MBContextCheckResponse(&context);
}
uint8_t*Mcontext::GetData(void)
{
	return context.buffer;
}
uint8_t Mcontext::GetLength(void)
{
	return MBContextGetLength(&context);
}
uint8_t Mcontext::GetFcode(void)
{
	return MBContextGetFcode(&context);
}
X03Request& Mcontext::GetX03Request(void)
{
	return *(X03Request*)this;
}
X03Response& Mcontext::GetX03Response(void)
{
	return *(X03Response*)this;
}
X10Request& Mcontext::GetX10Request(void)
{
	return *(X10Request*)this;
}
X10Response& Mcontext::GetX10Response(void)
{
	return *(X10Response*)this;
}

//xX03Request
bool X03Request::Check(void)
{
	return (X03RequestCheck((X03RequestContext*)&context) == 1);
}
uint8_t X03Request::GetSlave(void)
{
	return X03RequestGetSlave((X03RequestContext*)&context);
}
uint8_t X03Request::GetFcode(void)
{
	return X03RequestGetFcode((X03RequestContext*)&context);
}
uint16_t X03Request::GetOffset(void)
{
	return X03RequestGetOffset((X03RequestContext*)&context);
}
uint16_t X03Request::GetCount(void)
{
	return X03RequestGetCount((X03RequestContext*)&context);
}
uint16_t X03Request::CalcCrc(void)
{
	return X03RequestCalcCrc((X03RequestContext*)&context);
}
uint16_t X03Request::GetCrc(void)
{
	return X03RequestGetCrc((X03RequestContext*)&context);
}
uint8_t X03Request::GetLength(void)
{
	return X03RequestGetLength((X03RequestContext*)&context);
}
void X03Request::SetSlave(uint8_t slave)
{
	X03RequestSetSlave((X03RequestContext*)&context, slave);
}
void X03Request::SetFcode(uint8_t fcode)
{
	X03RequestSetFcode((X03RequestContext*)&context, fcode);
}
void X03Request::SetOffset(uint16_t offset)
{
	X03RequestSetOffset((X03RequestContext*)&context, offset);
}
void X03Request::SetCount(uint16_t count)
{
	X03RequestSetCount((X03RequestContext*)&context, count);
}
void X03Request::SetCrc(uint16_t crc)
{
	context.index = X03Request::GetLength();
	X03RequestSetCrc((X03RequestContext*)&context, crc);
}

//xX03Response
bool X03Response::Check(void)
{
	return (X03ResponseCheck((X03ResponseContext*)&context) == 1);
}
uint8_t X03Response::GetSlave(void)
{
	return X03ResponseGetSlave((X03ResponseContext*)&context);
}
uint8_t X03Response::GetFcode(void)
{
	return X03ResponseGetFcode((X03ResponseContext*)&context);
}
uint8_t X03Response::GetBcount(void)
{
	return X03ResponseGetBcount((X03ResponseContext*)&context);
}
uint16_t X03Response::GetData(uint8_t i)
{
	return X03ResponseGetData((X03ResponseContext*)&context, i);
}
uint16_t X03Response::CalcCrc(void)
{
	return X03ResponseCalcCrc((X03ResponseContext*)&context);
}
uint16_t X03Response::GetCrc(void)
{
	return X03ResponseGetCrc((X03ResponseContext*)&context);
}
uint8_t X03Response::GetLength(void)
{
	return X03ResponseGetLength((X03ResponseContext*)&context);
}
void X03Response::SetSlave(uint8_t slave)
{
	X03ResponseSetSlave((X03ResponseContext*)&context, slave);
}
void X03Response::SetFcode(uint8_t fcode)
{
	X03ResponseSetFcode((X03ResponseContext*)&context, fcode);
}
void X03Response::SetBcount(uint8_t bcount)
{
	X03ResponseSetBcount((X03ResponseContext*)&context, bcount);
}
void X03Response::SetData(uint8_t i, uint16_t data)
{
	X03ResponseSetData((X03ResponseContext*)&context, i, data);
}
void X03Response::SetCrc(uint16_t crc)
{
	context.index = X03Response::GetLength();
	X03ResponseSetCrc((X03ResponseContext*)&context, crc);
}

//xX10Request
bool X10Request::Check(void)
{
	return (X10RequestCheck((X10RequestContext*)&context) == 1);
}
uint8_t X10Request::GetSlave(void)
{
	return X10RequestGetSlave((X10RequestContext*)&context);
}
uint8_t X10Request::GetFcode(void)
{
	return X10RequestGetFcode((X10RequestContext*)&context);
}
uint16_t X10Request::GetOffset(void)
{
	return X10RequestGetOffset((X10RequestContext*)&context);
}
uint16_t X10Request::GetCount(void)
{
	return X10RequestGetCount((X10RequestContext*)&context);
}
uint8_t X10Request::GetBcount(void)
{
	return X10RequestGetBcount((X10RequestContext*)&context);
}
uint16_t X10Request::GetData(uint8_t i)
{
	return X10RequestGetData((X10RequestContext*)&context, i);
}
uint16_t X10Request::CalcCrc(void)
{
	return X10RequestCalcCrc((X10RequestContext*)&context);
}
uint16_t X10Request::GetCrc(void)
{
	return X10RequestGetCrc((X10RequestContext*)&context);
}
uint8_t X10Request::GetLength(void)
{
	return X10RequestGetLength((X10RequestContext*)&context);
}
void X10Request::SetSlave(uint8_t slave)
{
	X10RequestSetSlave((X10RequestContext*)&context, slave);
}
void X10Request::SetFcode(uint8_t fcode)
{
	X10RequestSetFcode((X10RequestContext*)&context, fcode);
}
void X10Request::SetOffset(uint16_t offset)
{
	X10RequestSetOffset((X10RequestContext*)&context, offset);
}
void X10Request::SetCount(uint16_t count)
{
	X10RequestSetCount((X10RequestContext*)&context, count);
}
void X10Request::SetBcount(uint8_t bcount)
{
	X10RequestSetCount((X10RequestContext*)&context, bcount);
}
void X10Request::SetData(uint8_t i, uint16_t data)
{
	X10RequestSetData((X10RequestContext*)&context, i, data);
}
void X10Request::SetCrc(uint16_t crc)
{
	context.index = X10Request::GetLength();
	X10RequestSetCrc((X10RequestContext*)&context, crc);
}

//xX10Response
bool X10Response::Check(void)
{
	return (X10ResponseCheck((X10ResponseContext*)&context) == 1);
}
uint8_t X10Response::GetSlave(void)
{
	return X10ResponseGetSlave((X10ResponseContext*)&context);
}
uint8_t X10Response::GetFcode(void)
{
	return X10ResponseGetFcode((X10ResponseContext*)&context);
}
uint16_t X10Response::GetOffset(void)
{
	return X10ResponseGetOffset((X10ResponseContext*)&context);
}
uint16_t X10Response::GetCount(void)
{
	return X10ResponseGetCount((X10ResponseContext*)&context);
}
uint16_t X10Response::CalcCrc(void)
{
	return X10ResponseCalcCrc((X10ResponseContext*)&context);
}
uint16_t X10Response::GetCrc(void)
{
	return X10ResponseGetCrc((X10ResponseContext*)&context);
}
uint8_t X10Response::GetLength(void)
{
	return X10ResponseGetLength((X10ResponseContext*)&context);
}
void X10Response::SetSlave(uint8_t slave)
{
	X10ResponseSetSlave((X10ResponseContext*)&context, slave);
}
void X10Response::SetFcode(uint8_t fcode)
{
	X10ResponseSetFcode((X10ResponseContext*)&context, fcode);
}
void X10Response::SetOffset(uint16_t offset)
{
	X10ResponseSetOffset((X10ResponseContext*)&context, offset);
}
void X10Response::SetCount(uint16_t count)
{
	X10ResponseSetCount((X10ResponseContext*)&context, count);
}
void X10Response::SetCrc(uint16_t crc)
{
	context.index = X10Response::GetLength();
	X10ResponseSetCrc((X10ResponseContext*)&context, crc);
}
