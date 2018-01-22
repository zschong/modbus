#include "modbusservice.h"



ModbusService::ModbusService(void)
{
	timeout = 0;
}
bool ModbusService::SetComConfig(const ComConfig& c)
{
	return modbus.Init(c.GetComName(), 
					   c.GetBaudRate(),
					   c.GetParity(),
					   c.GetByteSize(),
					   c.GetStopBit());
}
void ModbusService::AddVarConfig(int first, int second)
{
	IdCount().Add(varconfigmap, first, second);
	//varconfigmap[first] = second;
}
void ModbusService::DelVarConfig(int first, int second)
{
	IdCount().Del(varconfigmap, first, second);
	//varconfigmap.erase(offset);
}
bool ModbusService::SendX01Request(int first, int second)
{
	X01Request request;

	request.SetSlave( (uint8_t)(first >> 24) );
	request.SetFcode( (uint8_t)(first >> 16) );
	request.SetOffset( (uint16_t)(first >> 0) );
	request.SetCount( (uint16_t)(second >> 16) );
	request.SetCrc( request.CalcCrc() );
	printf("\nx01request:");
	request.Show();

	return modbus.SendRequest(request);
}
bool ModbusService::SendX02Request(int first, int second)
{
	X02Request request;

	request.SetSlave( (uint8_t)(first >> 24) );
	request.SetFcode( (uint8_t)(first >> 16) );
	request.SetOffset( (uint16_t)(first >> 0) );
	request.SetCount( (uint16_t)(second >> 16) );
	request.SetCrc( request.CalcCrc() );
	printf("\nx02request:");
	request.Show();

	return modbus.SendRequest(request);
}
bool ModbusService::SendX03Request(int first, int second)
{
	X03Request request;

	request.SetSlave( (uint8_t)(first >> 24) );
	request.SetFcode( (uint8_t)(first >> 16) );
	request.SetOffset( (uint16_t)(first >> 0) );
	request.SetCount( (uint16_t)(second >> 16) );
	request.SetCrc( request.CalcCrc() );
	//printf("\nx03request:");
	//request.Show();

	return modbus.SendRequest(request);
}
bool ModbusService::SendX04Request(int first, int second)
{
	X04Request request;

	request.SetSlave( (uint8_t)(first >> 24) );
	request.SetFcode( (uint8_t)(first >> 16) );
	request.SetOffset( (uint16_t)(first >> 0) );
	request.SetCount( (uint16_t)(second >> 16) );
	request.SetCrc( request.CalcCrc() );
	printf("\nx04request:");
	request.Show();

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
	int ret = modbus.RecvResponse();
	switch(ret)
	{
		case 0x01:
			GetX01Response(values);
			break;
		case 0x02:
			GetX02Response(values);
			break;
		case 0x03:
			GetX03Response(values);
			break;
		case 0x04:
			GetX04Response(values);
			break;
		case 0x05:
			GetX05Response(values);
			break;
		case 0x06:
			GetX06Response(values);
			break;
		case 0x0f:
			GetX0fResponse(values);
			break;
		case 0x10:
			GetX10Response(values);
			break;
		default:
			return false;
	}
	timeout = 0;
	modbus.InitResponse();
	return true;
}
bool ModbusService::SetValue(map<int,int>& values)
{
}
bool ModbusService::GetX01Response(map<int,int>& values)
{
	printf("%d(ms) x01response:", timer.mdiff());
	modbus.x01response.Show();
	return false;
}
bool ModbusService::GetX02Response(map<int,int>& values)
{
	printf("%d(ms) x02response:", timer.mdiff());
	modbus.x02response.Show();
	return false;
}
bool ModbusService::GetX03Response(map<int,int>& values)
{
	X03Request &x = modbus.GetContext().GetX03Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int count = x.GetCount();

	values.clear();
	for(int i = 0; i < count; i++)
	{
		int first = (slave << 24) | (fcode << 16) | (offset + i);
		int second = (modbus.x03response.GetData(i+1) << 16);
		values[first] = second;
	}
	//printf("%d(ms) x03response:", timer.mdiff());
	//modbus.x03response.Show();

	return (values.begin() != values.end());
}
bool ModbusService::GetX04Response(map<int,int>& values)
{
	printf("%d(ms) x04response:", timer.mdiff());
	modbus.x04response.Show();
	return false;
}
bool ModbusService::GetX05Response(map<int,int>& values)
{
	printf("%d(ms) x05response:", timer.mdiff());
	modbus.x05response.Show();
	return false;
}
bool ModbusService::GetX06Response(map<int,int>& values)
{
	printf("%d(ms) x06response:", timer.mdiff());
	modbus.x06response.Show();
	return false;
}
bool ModbusService::GetX0fResponse(map<int,int>& values)
{
	printf("%d(ms) x0fresponse:", timer.mdiff());
	modbus.x0fresponse.Show();
	return false;
}
bool ModbusService::GetX10Response(map<int,int>& values)
{
	printf("%d(ms) x10response:", timer.mdiff());
	modbus.x0fresponse.Show();
	modbus.x0fresponse.Show();
	return false;
}
