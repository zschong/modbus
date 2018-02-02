#include "modbusservice.h"


ModbusService::ModbusService(void):timeout(0),comid(0)
{
}
bool ModbusService::SetComConfig(const string& com, const ComConfig& comcfg)
{
	int baud = comcfg.GetBaudRate();
	int parity = comcfg.GetParity();
	int bsize = comcfg.GetByteSize();
	int stop = comcfg.GetStopBit();

	comconfig = comcfg;
	return modbus.Init(com, baud, parity, bsize, stop);
}
void ModbusService::AddVarConfig(RegisterOperator& x)
{
	x.Add(requestmap, x.GetKey(), x.GetValue());
}
const ComConfig& ModbusService::GetComConfig(void)
{
	return comconfig;
}
const map<unsigned,unsigned>& ModbusService::GetVarConfig(void)
{
	return requestmap;
}
bool ModbusService::SendRequest(void)
{
	if( requestlist.begin() == requestlist.end() )
	{
		for(Iterator i = requestmap.begin(); i != requestmap.end(); i++)
		{
			requestlist.push_back(RegisterOperator(i->first, i->second));
		}
	}
	if( requestlist.begin() == requestlist.end() )
	{
		return false;
	}
	timer.init();
	RegisterOperator &x = requestlist.front();
	switch( x.GetFcode() )
	{
		case 0x01:
			SendX01Request(x);
			break;
		case 0x02:
			SendX02Request(x);
			break;
		case 0x03:
			SendX03Request(x);
			break;
		case 0x04:
			SendX04Request(x);
			break;
		case 0x05:
			SendX05Request(x);
			break;
		case 0x06:
			SendX06Request(x);
			break;
		case 0x0f:
			SendX0fRequest(x);
			break;
		case 0x10:
			SendX10Request(x);
			break;
	}
	timeout = 1250;
	requestlist.pop_front();
	return true;
}
void ModbusService::DelVarConfig(RegisterOperator& x)
{
	x.Del(requestmap, x.GetKey(), x.GetValue());
}
bool ModbusService::SendX01Request(RegisterOperator& x)
{
	X01Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX02Request(RegisterOperator& x)
{
	X02Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX03Request(RegisterOperator& x)
{
	X03Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX04Request(RegisterOperator& x)
{
	X04Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX05Request(RegisterOperator& x)
{
	X05Request request;

	if( x.GetCount() != 0 )
	{
		x.SetCount(0xFF00);
	}
	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetValue( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX06Request(RegisterOperator& x)
{
	X06Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetValue( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX0fRequest(RegisterOperator& x)
{
	X0fRequest request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( 1 );
	request.SetBcount( 1 );
	request.SetCoil(1, x.GetCount() != 0);
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX10Request(RegisterOperator& x)
{
	X10Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( 1 );
	request.SetBcount( 2 );
	request.SetData(1, x.GetCount());
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SetValue(RegisterOperator& x)
{
	requestlist.push_back(x);
}
bool ModbusService::GetValue(list<RegisterOperator>& values)
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
bool ModbusService::GetX01Response(list<RegisterOperator>& idlist)
{
	X01Request &x = modbus.GetContext().GetX01Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int count = x.GetCount();

	idlist.clear();
	for(int i = 0; i < count; i++)
	{
		unsigned data = modbus.x01response.GetCoil(i + 1);
		RegisterOperator r(slave, fcode, (offset + i), data);
		idlist.push_back(r);
	}

	return (idlist.begin() != idlist.end());
}
bool ModbusService::GetX02Response(list<RegisterOperator>& idlist)
{
	X02Request &x = modbus.GetContext().GetX02Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int count = x.GetCount();

	idlist.clear();
	for(int i = 0; i < count; i++)
	{
		unsigned data = modbus.x02response.GetCoil(i + 1);
		RegisterOperator r(slave, fcode, (offset + i), data);
		idlist.push_back(r);
	}

	return (idlist.begin() != idlist.end());
}
bool ModbusService::GetX03Response(list<RegisterOperator>& idlist)
{
	X03Request &x = modbus.GetContext().GetX03Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int count = x.GetCount();

	idlist.clear();
	for(int i = 0; i < count; i++)
	{
		unsigned data = modbus.x03response.GetData(i + 1);
		RegisterOperator r(slave, fcode, (offset + i), data);
		idlist.push_back(r);
	}

	return (idlist.begin() != idlist.end());
}
bool ModbusService::GetX04Response(list<RegisterOperator>& idlist)
{
	X04Request &x = modbus.GetContext().GetX04Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int count = x.GetCount();

	idlist.clear();
	for(int i = 0; i < count; i++)
	{
		uint16_t data = modbus.x04response.GetData(i + 1);
		idlist.push_back(RegisterOperator(slave, fcode, (offset + i), data));
	}

	return (idlist.begin() != idlist.end());
}
bool ModbusService::GetX05Response(list<RegisterOperator>& idlist)
{
	X05Request &x = modbus.GetContext().GetX05Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int value = x.GetValue();

	idlist.clear();

	return (idlist.begin() != idlist.end());
}
bool ModbusService::GetX06Response(list<RegisterOperator>& idlist)
{
	X06Request &x = modbus.GetContext().GetX06Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int value = x.GetValue();

	idlist.clear();

	return (idlist.begin() != idlist.end());
}
bool ModbusService::GetX0fResponse(list<RegisterOperator>& idlist)
{
	X0fRequest &x = modbus.GetContext().GetX0fRequest();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int bcount = x.GetBcount();

	idlist.clear();

	return (idlist.begin() != idlist.end());
}
bool ModbusService::GetX10Response(list<RegisterOperator>& idlist)
{
	X10Request &x = modbus.GetContext().GetX10Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int bcount = x.GetBcount();

	idlist.clear();

	return (idlist.begin() != idlist.end());
}
