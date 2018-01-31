#include "modbusservice.h"



ModbusService::ModbusService(void)
{
	timeout = 0;
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
void ModbusService::AddVarConfig(IdCount& x)
{
	x.Add(varconfigmap, x.GetKey(), x.GetValue());
}
const ComConfig& ModbusService::GetComConfig(void)
{
	return comconfig;
}
const map<unsigned,unsigned>& ModbusService::GetVarConfig(void)
{
	return varconfigmap;
}
bool ModbusService::SendRequest(void)
{
	if( requestlist.begin() == requestlist.end() )
	{
		for(Iterator i = varconfigmap.begin(); i != varconfigmap.end(); i++)
		{
			requestlist.push_back(IdCount(i->first, i->second));
		}
	}
	if( requestlist.begin() == requestlist.end() )
	{
		return false;
	}
	timer.init();
	IdCount &x = requestlist.front();
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
void ModbusService::DelVarConfig(IdCount& x)
{
	x.Del(varconfigmap, x.GetKey(), x.GetValue());
}
bool ModbusService::SendX01Request(IdCount& x)
{
	X01Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX02Request(IdCount& x)
{
	X02Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX03Request(IdCount& x)
{
	X03Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX04Request(IdCount& x)
{
	X04Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX05Request(IdCount& x)
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
bool ModbusService::SendX06Request(IdCount& x)
{
	X06Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetValue( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX0fRequest(IdCount& x)
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
bool ModbusService::SendX10Request(IdCount& x)
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
bool ModbusService::SetValue(IdCount& x)
{
	requestlist.push_back(x);
}
bool ModbusService::GetValue(list<IdCount>& values)
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
bool ModbusService::GetX01Response(list<IdCount>& idlist)
{
	return false;
}
bool ModbusService::GetX02Response(list<IdCount>& idlist)
{
	return false;
}
bool ModbusService::GetX03Response(list<IdCount>& idlist)
{
	X03Request &x = modbus.GetContext().GetX03Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int count = x.GetCount();

	idlist.clear();
	for(int i = 0; i < count; i++)
	{
		uint16_t data = modbus.x03response.GetData(i + 1);
		idlist.push_back(IdCount(slave, fcode, (offset + i), data));
	}

	return (idlist.begin() != idlist.end());
}
bool ModbusService::GetX04Response(list<IdCount>& idlist)
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
		idlist.push_back(IdCount(slave, fcode, (offset + i), data));
	}

	return (idlist.begin() != idlist.end());
}
bool ModbusService::GetX05Response(list<IdCount>& idlist)
{
	X05Request &x = modbus.GetContext().GetX05Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int value = x.GetValue();

	idlist.clear();

	return (idlist.begin() != idlist.end());
}
bool ModbusService::GetX06Response(list<IdCount>& idlist)
{
	X06Request &x = modbus.GetContext().GetX06Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int value = x.GetValue();

	idlist.clear();

	return (idlist.begin() != idlist.end());
}
bool ModbusService::GetX0fResponse(list<IdCount>& idlist)
{
	X0fRequest &x = modbus.GetContext().GetX0fRequest();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int bcount = x.GetBcount();

	idlist.clear();

	return (idlist.begin() != idlist.end());
}
bool ModbusService::GetX10Response(list<IdCount>& idlist)
{
	X10Request &x = modbus.GetContext().GetX10Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int bcount = x.GetBcount();

	idlist.clear();

	return (idlist.begin() != idlist.end());
}
