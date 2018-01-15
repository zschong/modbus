#include "modbusservice.h"

ModbusService::ModbusService(void)
{
	timeout = 0;
}
bool ModbusService::ComConfig(ComConfig& c)
{
	return modbus.Init(c.GetComName(), 
					   c.GetBaudRate(),
					   c.GetParity(),
					   c.GetByteSize(),
					   c.GetStopBit());
}
void ModbusService::AddVarConfig(int offset, int count)
{
	switch( offset >> 16 )
	{
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
			varconfigmap[offset] = count;
	}
}
void ModbusService::DelVarConfig(int offset, int count)
{
	varconfigmap.erase(offset);
}
bool ModbusService::SendX01Request(int first, int second)
{
	X01Request request;

	request.SetSlave((uint8_t)offset >> 24);
	request.SetFcode((uint8_t)offset >> 16);
	request.SetOffset((uint16_t)offset >> 0);
	request.SetCount((uint16_t)count >> 16);
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX02Request(int first, int second)
{
	X02Request request;

	request.SetSlave((uint8_t)offset >> 24);
	request.SetFcode((uint8_t)offset >> 16);
	request.SetOffset((uint16_t)offset >> 0);
	request.SetCount((uint16_t)count >> 16);
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX03Request(int first, int second)
{
	X03Request request;

	request.SetSlave((uint8_t)offset >> 24);
	request.SetFcode((uint8_t)offset >> 16);
	request.SetOffset((uint16_t)offset >> 0);
	request.SetCount((uint16_t)count >> 16);
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX04Request(int first, int second)
{
	X04Request request;

	request.SetSlave((uint8_t)offset >> 24);
	request.SetFcode((uint8_t)offset >> 16);
	request.SetOffset((uint16_t)offset >> 0);
	request.SetCount((uint16_t)count >> 16);
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendRequest(void)
{
	if( requestmap.begin() == requestmap.end() )
	{
		requestmap = varconfigmap;
	}
	if( requestmap.begin() == requestmap.end() )
	{
		return false;
	}
	map<int,int>::iterator i = requestmap.begin();
	switch( 0xff & (i->first >> 16) )
	{
		case 0x01:
			SendX01Request(i->first, i->second);
			break;
		case 0x02:
			SendX02Request(i->first, i->second);
			break;
		case 0x03:
			SendX03Request(i->first, i->second);
			break;
		case 0x04:
			SendX04Request(i->first, i->second);
			break;
	}
	timer.init();
	timeout = (uint8_t)(i->second >> 8);
	requestmap.erase(i->first);
	return true;
}
bool ModbusService::GetValue(map<int,int>& values)
{
	if( timer.mdiff() > timeout )
	{
		SendRequest();
	}
	int ret modbus.RecvResponse();
	if( 0 != ret )
	{
		modbus.ResponseShow(ret);
		modbus.InitResponse();
	}
}
bool ModbusService::SetValue(map<int,int>& values)
{
}
