#include <stdio.h>
#include <string.h>
#include "mcontext.h"

Mcontext::Mcontext(void)
{
	Init();
}
void Mcontext::Init(void)
{
	MBContextInit(&context);
}
void Mcontext::Show(void)
{
	printf("[");
	for(int i = 0; i < GetLength(); i++)
	{
		printf("%02X ", context.buffer[i]);
	}
	printf("\b].%s\n", Check() ? "ok" : "xx");
	fflush(stdout);
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
bool Mcontext::Check(void)
{
	return false;
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
uint8_t Mcontext::GetMaster(void)
{
	return context.master;
}
uint8_t Mcontext::GetServiceFcode(void)
{
	return context.service_fcode;
}
void Mcontext::SetMaster(uint8_t master)
{
	MBContextSetMaster(&context, master);
}
void Mcontext::SetServiceFcode(uint8_t sfcode)
{
	MBContextSetServiceFcode(&context, sfcode);
}
Mcontext& Mcontext::operator=(const Mcontext& m)
{
	memcpy(&context, &m.context, sizeof(context));
	context.index = ((Mcontext*)&m)->GetLength();
	return *this;
}

//GetRequest
X01Request& Mcontext::GetX01Request(void)
{
	return *(X01Request*)this;
}
X02Request& Mcontext::GetX02Request(void)
{
	return *(X02Request*)this;
}
X03Request& Mcontext::GetX03Request(void)
{
	return *(X03Request*)this;
}
X04Request& Mcontext::GetX04Request(void)
{
	return *(X04Request*)this;
}
X05Request& Mcontext::GetX05Request(void)
{
	return *(X05Request*)this;
}
X06Request& Mcontext::GetX06Request(void)
{
	return *(X06Request*)this;
}
X0fRequest& Mcontext::GetX0fRequest(void)
{
	return *(X0fRequest*)this;
}
X10Request& Mcontext::GetX10Request(void)
{
	return *(X10Request*)this;
}

//GetResponse
X01Response& Mcontext::GetX01Response(void)
{
	return *(X01Response*)this;
}
X02Response& Mcontext::GetX02Response(void)
{
	return *(X02Response*)this;
}
X03Response& Mcontext::GetX03Response(void)
{
	return *(X03Response*)this;
}
X04Response& Mcontext::GetX04Response(void)
{
	return *(X04Response*)this;
}
X05Response& Mcontext::GetX05Response(void)
{
	return *(X05Response*)this;
}
X06Response& Mcontext::GetX06Response(void)
{
	return *(X06Response*)this;
}
X0fResponse& Mcontext::GetX0fResponse(void)
{
	return *(X0fResponse*)this;
}
X10Response& Mcontext::GetX10Response(void)
{
	return *(X10Response*)this;
}

//X01Request
X01Request::X01Request(void)
{
	context.service_fcode = 0x01;
}
X01Request::X01Request(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	Set(slave, fcode, offset, count);
}
bool X01Request::Check(void)
{
	context.service_fcode = 0x01;
	return (X01RequestCheck((X01RequestContext*)&context) == 1);
}
uint8_t X01Request::GetSlave(void)
{
	return X01RequestGetSlave((X01RequestContext*)&context);
}
uint8_t X01Request::GetFcode(void)
{
	return X01RequestGetFcode((X01RequestContext*)&context);
}
uint16_t X01Request::GetOffset(void)
{
	return X01RequestGetOffset((X01RequestContext*)&context);
}
uint16_t X01Request::GetCount(void)
{
	return X01RequestGetCount((X01RequestContext*)&context);
}
uint16_t X01Request::CalcCrc(void)
{
	return X01RequestCalcCrc((X01RequestContext*)&context);
}
uint16_t X01Request::GetCrc(void)
{
	return X01RequestGetCrc((X01RequestContext*)&context);
}
uint8_t X01Request::GetLength(void)
{
	return X01RequestGetLength((X01RequestContext*)&context);
}
void X01Request::SetSlave(uint8_t slave)
{
	return X01RequestSetSlave((X01RequestContext*)&context, slave);
}
void X01Request::SetFcode(uint8_t fcode)
{
	return X01RequestSetFcode((X01RequestContext*)&context, fcode);
}
void X01Request::SetOffset(uint16_t offset)
{
	return X01RequestSetOffset((X01RequestContext*)&context, offset);
}
void X01Request::SetCount(uint16_t count)
{
	return X01RequestSetCount((X01RequestContext*)&context, count);
}
void X01Request::SetCrc(uint16_t crc)
{
	return X01RequestSetCrc((X01RequestContext*)&context, crc);
}
void X01Request::Set(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetCount(count);
	SetCrc( CalcCrc() );
}

//X02Request
X02Request::X02Request(void)
{
	context.service_fcode = 0x02;
}
X02Request::X02Request(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	Set(slave, fcode, offset, count);
}
bool X02Request::Check(void)
{
	context.service_fcode = 0x02;
	return (X02RequestCheck((X02RequestContext*)&context) == 1);
}
uint8_t X02Request::GetSlave(void)
{
	return X02RequestGetSlave((X02RequestContext*)&context);
}
uint8_t X02Request::GetFcode(void)
{
	return X02RequestGetFcode((X02RequestContext*)&context);
}
uint16_t X02Request::GetOffset(void)
{
	return X02RequestGetOffset((X02RequestContext*)&context);
}
uint16_t X02Request::GetCount(void)
{
	return X02RequestGetCount((X02RequestContext*)&context);
}
uint16_t X02Request::CalcCrc(void)
{
	return X02RequestCalcCrc((X02RequestContext*)&context);
}
uint16_t X02Request::GetCrc(void)
{
	return X02RequestGetCrc((X02RequestContext*)&context);
}
uint8_t X02Request::GetLength(void)
{
	return X02RequestGetLength((X02RequestContext*)&context);
}
void X02Request::SetSlave(uint8_t slave)
{
	return X02RequestSetSlave((X02RequestContext*)&context, slave);
}
void X02Request::SetFcode(uint8_t fcode)
{
	return X02RequestSetFcode((X02RequestContext*)&context, fcode);
}
void X02Request::SetOffset(uint16_t offset)
{
	return X02RequestSetOffset((X02RequestContext*)&context, offset);
}
void X02Request::SetCount(uint16_t count)
{
	return X02RequestSetCount((X02RequestContext*)&context, count);
}
void X02Request::SetCrc(uint16_t crc)
{
	return X02RequestSetCrc((X02RequestContext*)&context, crc);
}
void X02Request::Set(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetCount(count);
	SetCrc( CalcCrc() );
}

//xX03Request
X03Request::X03Request(void)
{
	context.service_fcode = 0x03;
}
X03Request::X03Request(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	Set(slave, fcode, offset, count);
}
bool X03Request::Check(void)
{
	context.service_fcode = 0x03;
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
void X03Request::Set(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetCount(count);
	SetCrc( CalcCrc() );
	printf("%d,%d,%d,%d\n", slave, fcode, offset, count);
	Show();
}


//X04Request
X04Request::X04Request(void)
{
	context.service_fcode = 0x04;
}
X04Request::X04Request(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	Set(slave, fcode, offset, count);
}
bool X04Request::Check(void)
{
	context.service_fcode = 0x04;
	return (X04RequestCheck((X04RequestContext*)&context) == 1);
}
uint8_t X04Request::GetSlave(void)
{
	return X04RequestGetSlave((X04RequestContext*)&context);
}
uint8_t X04Request::GetFcode(void)
{
	return X04RequestGetFcode((X04RequestContext*)&context);
}
uint16_t X04Request::GetOffset(void)
{
	return X04RequestGetOffset((X04RequestContext*)&context);
}
uint16_t X04Request::GetCount(void)
{
	return X04RequestGetCount((X04RequestContext*)&context);
}
uint16_t X04Request::CalcCrc(void)
{
	return X04RequestCalcCrc((X04RequestContext*)&context);
}
uint16_t X04Request::GetCrc(void)
{
	return X04RequestGetCrc((X04RequestContext*)&context);
}
uint8_t X04Request::GetLength(void)
{
	return X04RequestGetLength((X04RequestContext*)&context);
}
void X04Request::SetSlave(uint8_t slave)
{
	X04RequestSetSlave((X04RequestContext*)&context, slave);
}
void X04Request::SetFcode(uint8_t fcode)
{
	X04RequestSetFcode((X04RequestContext*)&context, fcode);
}
void X04Request::SetOffset(uint16_t offset)
{
	X04RequestSetOffset((X04RequestContext*)&context, offset);
}
void X04Request::SetCount(uint16_t count)
{
	X04RequestSetCount((X04RequestContext*)&context, count);
}
void X04Request::SetCrc(uint16_t crc)
{
	context.index = GetLength();
	X03RequestSetCrc((X03RequestContext*)&context, crc);
}
void X04Request::Set(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetCount(count);
	SetCrc( CalcCrc() );
}

//X05Request
X05Request::X05Request(void)
{
	context.service_fcode = 0x05;
}
X05Request::X05Request(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	Set(slave, fcode, offset, count);
}
bool X05Request::Check(void)
{
	context.service_fcode = 0x05;
	return (X05RequestCheck((X05RequestContext*)&context) == 1);
}
uint8_t X05Request::GetSlave(void)
{
	return X05RequestGetSlave((X05RequestContext*)&context);
}
uint8_t X05Request::GetFcode(void)
{
	return X05RequestGetFcode((X05RequestContext*)&context);
}
uint16_t X05Request::GetOffset(void)
{
	return X05RequestGetOffset((X05RequestContext*)&context);
}
uint16_t X05Request::GetValue(void)
{
	return X05RequestGetValue((X05RequestContext*)&context);
}
uint16_t X05Request::CalcCrc(void)
{
	return X05RequestCalcCrc((X05RequestContext*)&context);
}
uint16_t X05Request::GetCrc(void)
{
	return X05RequestGetCrc((X05RequestContext*)&context);
}
uint8_t X05Request::GetLength(void)
{
	return X05RequestGetLength((X05RequestContext*)&context);
}
void X05Request::SetSlave(uint8_t slave)
{
	X05RequestSetSlave((X05RequestContext*)&context, slave);
}
void X05Request::SetFcode(uint8_t fcode)
{
	X05RequestSetFcode((X05RequestContext*)&context, fcode);
}
void X05Request::SetOffset(uint16_t offset)
{
	X05RequestSetOffset((X05RequestContext*)&context, offset);
}
void X05Request::SetValue(uint16_t value)
{
	X05RequestSetValue((X05RequestContext*)&context, value);
}
void X05Request::SetCrc(uint16_t crc)
{
	X05RequestSetCrc((X05RequestContext*)&context, crc);
}
void X05Request::Set(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t value)
{
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetValue(value);
	SetCrc( CalcCrc() );
}

//X06Request
X06Request::X06Request(void)
{
	context.service_fcode = 0x06;
}
X06Request::X06Request(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	Set(slave, fcode, offset, count);
}
bool X06Request::Check(void)
{
	context.service_fcode = 0x06;
	return (X06RequestCheck((X06RequestContext*)&context) == 1);
}
uint8_t X06Request::GetSlave(void)
{
	return X06RequestGetSlave((X06RequestContext*)&context);
}
uint8_t X06Request::GetFcode(void)
{
	return X06RequestGetFcode((X06RequestContext*)&context);
}
uint16_t X06Request::GetOffset(void)
{
	return X06RequestGetOffset((X06RequestContext*)&context);
}
uint16_t X06Request::GetValue(void)
{
	return X06RequestGetValue((X06RequestContext*)&context);
}
uint16_t X06Request::CalcCrc(void)
{
	return X06RequestCalcCrc((X06RequestContext*)&context);
}
uint16_t X06Request::GetCrc(void)
{
	return X06RequestGetCrc((X06RequestContext*)&context);
}
uint8_t X06Request::GetLength(void)
{
	return X06RequestGetLength((X06RequestContext*)&context);
}
void X06Request::SetSlave(uint8_t slave)
{
	X06RequestSetSlave((X06RequestContext*)&context, slave);
}
void X06Request::SetFcode(uint8_t fcode)
{
	X06RequestSetFcode((X06RequestContext*)&context, fcode);
}
void X06Request::SetOffset(uint16_t offset)
{
	X06RequestSetOffset((X06RequestContext*)&context, offset);
}
void X06Request::SetValue(uint16_t value)
{
	X06RequestSetValue((X06RequestContext*)&context, value);
}
void X06Request::SetCrc(uint16_t crc)
{
	X06RequestSetCrc((X06RequestContext*)&context, crc);
}
void X06Request::Set(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t value)
{
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetValue(value);
	SetCrc( CalcCrc() );
}

//X0fRequest
X0fRequest::X0fRequest(void)
{
	context.service_fcode = 0x0f;
}
bool X0fRequest::Check(void)
{
	context.service_fcode = 0x0f;
	return (X0fRequestCheck((X0fRequestContext*)&context) == 1);
}
uint8_t X0fRequest::GetSlave(void)
{
	return X0fRequestGetSlave((X0fRequestContext*)&context);
}
uint8_t X0fRequest::GetFcode(void)
{
	return X0fRequestGetFcode((X0fRequestContext*)&context);
}
uint16_t X0fRequest::GetOffset(void)
{
	return X0fRequestGetOffset((X0fRequestContext*)&context);
}
uint16_t X0fRequest::GetCount(void)
{
	return X0fRequestGetCount((X0fRequestContext*)&context);
}
uint16_t X0fRequest::GetBcount(void)
{
	return X0fRequestGetBcount((X0fRequestContext*)&context);
}
uint16_t X0fRequest::GetCoil(uint16_t i)
{
	return X0fRequestGetCoil((X0fRequestContext*)&context, i);
}
uint16_t X0fRequest::CalcCrc(void)
{
	return X0fRequestCalcCrc((X0fRequestContext*)&context);
}
uint16_t X0fRequest::GetCrc(void)
{
	return X0fRequestGetCrc((X0fRequestContext*)&context);
}
uint8_t X0fRequest::GetLength(void)
{
	return X0fRequestGetLength((X0fRequestContext*)&context);
}
void X0fRequest::SetSlave(uint8_t slave)
{
	X0fRequestSetSlave((X0fRequestContext*)&context, slave);
}
void X0fRequest::SetFcode(uint8_t fcode)
{
	X0fRequestSetFcode((X0fRequestContext*)&context, fcode);
}
void X0fRequest::SetOffset(uint16_t offset)
{
	X0fRequestSetOffset((X0fRequestContext*)&context, offset);
}
void X0fRequest::SetCount(uint16_t count)
{
	X0fRequestSetCount((X0fRequestContext*)&context, count);
}
void X0fRequest::SetBcount(uint8_t bcount)
{
	X0fRequestSetBcount((X0fRequestContext*)&context, bcount);
}
void X0fRequest::SetCoil(uint16_t i, uint8_t status)
{
	X0fRequestSetCoil((X0fRequestContext*)&context, i, status);
}
void X0fRequest::SetCrc(uint16_t crc)
{
	X0fRequestSetCrc((X0fRequestContext*)&context, crc);
}

//X10Request
X10Request::X10Request(void)
{
	context.service_fcode = 0x10;
}
bool X10Request::Check(void)
{
	context.service_fcode = 0x10;
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
	X10RequestSetBcount((X10RequestContext*)&context, bcount);
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

//X01Response
X01Response::X01Response(void)
{
	context.service_fcode = 0x01;
}
bool X01Response::Check(void)
{
	context.service_fcode = 0x01;
	return (X01ResponseCheck((X01ResponseContext*)&context) == 1);
}
uint8_t X01Response::GetSlave(void)
{
	return X01ResponseGetSlave((X01ResponseContext*)&context);
}
uint8_t X01Response::GetFcode(void)
{
	return X01ResponseGetFcode((X01ResponseContext*)&context);
}
uint8_t X01Response::GetBcount(void)
{
	return X01ResponseGetBcount((X01ResponseContext*)&context);
}
uint16_t X01Response::GetCoil(uint16_t i)
{
	return X01ResponseGetCoil((X01ResponseContext*)&context, i);
}
uint16_t X01Response::CalcCrc(void)
{
	return X01ResponseCalcCrc((X01ResponseContext*)&context);
}
uint16_t X01Response::GetCrc(void)
{
	return X01ResponseGetCrc((X01ResponseContext*)&context);
}
uint8_t X01Response::GetLength(void)
{
	return X01ResponseGetLength((X01ResponseContext*)&context);
}
void X01Response::SetSlave(uint8_t slave)
{
	X01ResponseSetSlave((X01ResponseContext*)&context, slave);
}
void X01Response::SetFcode(uint8_t fcode)
{
	X01ResponseSetFcode((X01ResponseContext*)&context, fcode);
}
void X01Response::SetBcount(uint8_t bcount)
{
	X01ResponseSetBcount((X01ResponseContext*)&context, bcount);
}
void X01Response::SetCoil(uint16_t i, uint8_t status)
{
	X01ResponseSetCoil((X01ResponseContext*)&context, i, status);
}
void X01Response::SetCrc(uint16_t crc)
{
	X01ResponseSetCrc((X01ResponseContext*)&context, crc);
}

//X02Response
X02Response::X02Response(void)
{
	context.service_fcode = 0x02;
}
bool X02Response::Check(void)
{
	context.service_fcode = 0x02;
	return (X02ResponseCheck((X02ResponseContext*)&context) == 1);
}
uint8_t X02Response::GetSlave(void)
{
	return X02ResponseGetSlave((X02ResponseContext*)&context);
}
uint8_t X02Response::GetFcode(void)
{
	return X02ResponseGetFcode((X02ResponseContext*)&context);
}
uint8_t X02Response::GetBcount(void)
{
	return X02ResponseGetBcount((X02ResponseContext*)&context);
}
uint16_t X02Response::GetCoil(uint16_t i)
{
	return X02ResponseGetCoil((X02ResponseContext*)&context, i);
}
uint16_t X02Response::CalcCrc(void)
{
	return X02ResponseCalcCrc((X02ResponseContext*)&context);
}
uint16_t X02Response::GetCrc(void)
{
	return X02ResponseGetCrc((X02ResponseContext*)&context);
}
uint8_t X02Response::GetLength(void)
{
	return X02ResponseGetLength((X02ResponseContext*)&context);
}
void X02Response::SetSlave(uint8_t slave)
{
	X02ResponseSetSlave((X02ResponseContext*)&context, slave);
}
void X02Response::SetFcode(uint8_t fcode)
{
	X02ResponseSetFcode((X02ResponseContext*)&context, fcode);
}
void X02Response::SetBcount(uint8_t bcount)
{
	X02ResponseSetBcount((X02ResponseContext*)&context, bcount);
}
void X02Response::SetCoil(uint16_t i, uint8_t status)
{
	X02ResponseSetCoil((X02ResponseContext*)&context, i, status);
}
void X02Response::SetCrc(uint16_t crc)
{
	X02ResponseSetCrc((X02ResponseContext*)&context, crc);
}

//xX03Response
X03Response::X03Response(void)
{
	context.service_fcode = 0x03;
}
bool X03Response::Check(void)
{
	context.service_fcode = 0x03;
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

//X04Response
X04Response::X04Response(void)
{
	context.service_fcode = 0x04;
}
bool X04Response::Check(void)
{
	context.service_fcode = 0x04;
	return (X04ResponseCheck((X04ResponseContext*)&context) == 1);
}
uint8_t X04Response::GetSlave(void)
{
	return X04ResponseGetSlave((X04ResponseContext*)&context);
}
uint8_t X04Response::GetFcode(void)
{
	return X04ResponseGetFcode((X04ResponseContext*)&context);
}
uint8_t X04Response::GetBcount(void)
{
	return X04ResponseGetBcount((X04ResponseContext*)&context);
}
uint16_t X04Response::GetData(uint8_t i)
{
	return X04ResponseGetData((X04ResponseContext*)&context, i);
}
uint16_t X04Response::CalcCrc(void)
{
	return X04ResponseCalcCrc((X04ResponseContext*)&context);
}
uint16_t X04Response::GetCrc(void)
{
	return X04ResponseGetCrc((X04ResponseContext*)&context);
}
uint8_t X04Response::GetLength(void)
{
	return X04ResponseGetLength((X04ResponseContext*)&context);
}
void X04Response::SetSlave(uint8_t slave)
{
	X04ResponseSetSlave((X04ResponseContext*)&context, slave);
}
void X04Response::SetFcode(uint8_t fcode)
{
	X04ResponseSetFcode((X04ResponseContext*)&context, fcode);
}
void X04Response::SetBcount(uint8_t bcount)
{
	X04ResponseSetBcount((X04ResponseContext*)&context, bcount);
}
void X04Response::SetData(uint8_t i, uint16_t data)
{
	X04ResponseSetData((X04ResponseContext*)&context, i, data);
}
void X04Response::SetCrc(uint16_t crc)
{
	context.index = X04Response::GetLength();
	X04ResponseSetCrc((X04ResponseContext*)&context, crc);
}

//X05Response
X05Response::X05Response(void)
{
	context.service_fcode = 0x06;
}
X05Response::X05Response(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	Set(slave, fcode, offset, count);
}
bool X05Response::Check(void)
{
	context.service_fcode = 0x06;
	return (X05ResponseCheck((X05ResponseContext*)&context) == 1);
}
uint8_t X05Response::GetSlave(void)
{
	return X05ResponseGetSlave((X05ResponseContext*)&context);
}
uint8_t X05Response::GetFcode(void)
{
	return X05ResponseGetFcode((X05ResponseContext*)&context);
}
uint8_t X05Response::GetOffset(void)
{
	return X05ResponseGetOffset((X05ResponseContext*)&context);
}
uint16_t X05Response::GetValue(void)
{
	return X05ResponseGetValue((X05ResponseContext*)&context);
}
uint16_t X05Response::CalcCrc(void)
{
	return X05ResponseCalcCrc((X05ResponseContext*)&context);
}
uint16_t X05Response::GetCrc(void)
{
	return X05ResponseGetCrc((X05ResponseContext*)&context);
}
uint8_t X05Response::GetLength(void)
{
	return X05ResponseGetLength((X05ResponseContext*)&context);
}
void X05Response::SetSlave(uint8_t slave)
{
	X05ResponseSetSlave((X05ResponseContext*)&context, slave);
}
void X05Response::SetFcode(uint8_t fcode)
{
	X05ResponseSetFcode((X05ResponseContext*)&context, fcode);
}
void X05Response::SetOffset(uint16_t offset)
{
	X05ResponseSetOffset((X05ResponseContext*)&context, offset);
}
void X05Response::SetValue(uint16_t value)
{
	X05ResponseSetValue((X05ResponseContext*)&context, value);
}
void X05Response::SetCrc(uint16_t crc)
{
	X05ResponseSetCrc((X05ResponseContext*)&context, crc);
}
void X05Response::Set(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t value)
{
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetValue(value);
	SetCrc( CalcCrc() );
}

//X06Response
X06Response::X06Response(void)
{
	context.service_fcode = 0x06;
}
X06Response::X06Response(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	Set(slave, fcode, offset, count);
}
bool X06Response::Check(void)
{
	context.service_fcode = 0x06;
	return (X06ResponseCheck((X06ResponseContext*)&context) == 1);
}
uint8_t X06Response::GetSlave(void)
{
	return X06ResponseGetSlave((X06ResponseContext*)&context);
}
uint8_t X06Response::GetFcode(void)
{
	return X06ResponseGetFcode((X06ResponseContext*)&context);
}
uint8_t X06Response::GetOffset(void)
{
	return X06ResponseGetOffset((X06ResponseContext*)&context);
}
uint16_t X06Response::GetValue(void)
{
	return X06ResponseGetValue((X06ResponseContext*)&context);
}
uint16_t X06Response::CalcCrc(void)
{
	return X06ResponseCalcCrc((X06ResponseContext*)&context);
}
uint16_t X06Response::GetCrc(void)
{
	return X06ResponseGetCrc((X06ResponseContext*)&context);
}
uint8_t X06Response::GetLength(void)
{
	return X06ResponseGetLength((X06ResponseContext*)&context);
}
void X06Response::SetSlave(uint8_t slave)
{
	X06ResponseSetSlave((X06ResponseContext*)&context, slave);
}
void X06Response::SetFcode(uint8_t fcode)
{
	X06ResponseSetFcode((X06ResponseContext*)&context, fcode);
}
void X06Response::SetOffset(uint16_t offset)
{
	X06ResponseSetOffset((X06ResponseContext*)&context, offset);
}
void X06Response::SetValue(uint16_t value)
{
	X06ResponseSetValue((X06ResponseContext*)&context, value);
}
void X06Response::SetCrc(uint16_t crc)
{
	X06ResponseSetCrc((X06ResponseContext*)&context, crc);
}
void X06Response::Set(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t value)
{
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetValue(value);
	SetCrc( CalcCrc() );
}

//X0fResponse
X0fResponse::X0fResponse(void)
{
	context.service_fcode = 0x0f;
}
X0fResponse::X0fResponse(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	Set(slave, fcode, offset, count);
}
bool X0fResponse::Check(void)
{
	context.service_fcode = 0x0f;
	return (X0fResponseCheck((X0fResponseContext*)&context) == 1);
}
uint8_t X0fResponse::GetSlave(void)
{
	return X0fResponseGetSlave((X0fResponseContext*)&context);
}
uint8_t X0fResponse::GetFcode(void)
{
	return X0fResponseGetFcode((X0fResponseContext*)&context);
}
uint16_t X0fResponse::GetOffset(void)
{
	return X0fResponseGetOffset((X0fResponseContext*)&context);
}
uint16_t X0fResponse::GetCount(void)
{
	return X0fResponseGetCount((X0fResponseContext*)&context);
}
uint16_t X0fResponse::CalcCrc(void)
{
	return X0fResponseCalcCrc((X0fResponseContext*)&context);
}
uint16_t X0fResponse::GetCrc(void)
{
	return X0fResponseGetCrc((X0fResponseContext*)&context);
}
uint8_t X0fResponse::GetLength(void)
{
	return X0fResponseGetLength((X0fResponseContext*)&context);
}
void X0fResponse::SetSlave(uint8_t slave)
{
	X0fResponseSetSlave((X0fResponseContext*)&context, slave);
}
void X0fResponse::SetFcode(uint8_t fcode)
{
	X0fResponseSetFcode((X0fResponseContext*)&context, fcode);
}
void X0fResponse::SetOffset(uint16_t offset)
{
	X0fResponseSetOffset((X0fResponseContext*)&context, offset);
}
void X0fResponse::SetCount(uint16_t count)
{
	X0fResponseSetCount((X0fResponseContext*)&context, count);
}
void X0fResponse::SetCrc(uint16_t crc)
{
	X0fResponseSetCrc((X0fResponseContext*)&context, crc);
}
void X0fResponse::Set(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetCount(count);
	SetCrc( CalcCrc() );
}

//X10Response
X10Response::X10Response(void)
{
	context.service_fcode = 0x10;
}
X10Response::X10Response(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	Set(slave, fcode, offset, count);
}
bool X10Response::Check(void)
{
	context.service_fcode = 0x10;
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
void X10Response::Set(uint8_t slave, uint8_t fcode, uint16_t offset, uint16_t count)
{
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetCount(count);
	SetCrc( CalcCrc() );
}
