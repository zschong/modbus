#include "modbusservice.h"


ModbusService::ModbusService(void):timeout(0)
{
}
bool ModbusService::SetComConfig(const string& n, int b, int p, int z, int s)
{
	printf("%s(%s, %d, %d, %d, %d)\n", __func__, n.data(), b, p, z, s);
	return modbus.Init(n, b, p, z, s);
}
void ModbusService::AddVarConfig(VarOperator& x)
{
	printf("%s.comid(%d).slave(%d).fcode(%d).offset(%d).count(%d).interval(%d)\n",
			__func__, 
			x.GetComId(), 
			x.GetSlave(), 
			x.GetFcode(), 
			x.GetOffset(),
			x.GetCount(),
			x.GetInterval()
			);
	x.Add(requestmap, x.GetKey(), x.GetValue());
}
bool ModbusService::SendRequest(void)
{
	typedef map<unsigned,unsigned>::iterator Iterator;

	if( requestlist.begin() == requestlist.end() )
	{
		for(Iterator i = requestmap.begin(); i != requestmap.end(); i++)
		{
			requestlist.push_back(VarOperator(i->first, i->second));
		}
	}
	if( requestlist.begin() == requestlist.end() )
	{
		return false;
	}
	timer.init();
	VarOperator &x = requestlist.front();
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
	timeout = x.GetInterval();
	if( timeout < 100 )
	{
		timeout = 100;
	}
	requestlist.pop_front();
	return true;
}
void ModbusService::DelVarConfig(VarOperator& x)
{
	x.Del(requestmap, x.GetKey(), x.GetValue());
}
bool ModbusService::SendX01Request(VarOperator& x)
{
	X01Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX02Request(VarOperator& x)
{
	X02Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX03Request(VarOperator& x)
{
	X03Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX04Request(VarOperator& x)
{
	X04Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetCount( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX05Request(VarOperator& x)
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
bool ModbusService::SendX06Request(VarOperator& x)
{
	X06Request request;

	request.SetSlave( x.GetSlave() );
	request.SetFcode( x.GetFcode() );
	request.SetOffset( x.GetOffset() );
	request.SetValue( x.GetCount() );
	request.SetCrc( request.CalcCrc() );

	return modbus.SendRequest(request);
}
bool ModbusService::SendX0fRequest(VarOperator& x)
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
bool ModbusService::SendX10Request(VarOperator& x)
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
bool ModbusService::SetValue(VarOperator& x)
{
	requestlist.push_back(x);
}
unsigned ModbusService::GetValue(list<VarOperator>& values)
{
	if( timer.mdiff() > timeout )
	{
		SendRequest();
	}
	int ret = modbus.RecvResponse();
	switch(ret)
	{
		case 0x01:
			recvcount[ GetX01Response(values) ]++;
			break;
		case 0x02:
			recvcount[ GetX02Response(values) ]++;
			break;
		case 0x03:
			recvcount[ GetX03Response(values) ]++;
			break;
		case 0x04:
			recvcount[ GetX04Response(values) ]++;
			break;
		case 0x05:
			recvcount[ GetX05Response(values) ]++;
			break;
		case 0x06:
			recvcount[ GetX06Response(values) ]++;
			break;
		case 0x0f:
			recvcount[ GetX0fResponse(values) ]++;
			break;
		case 0x10:
			recvcount[ GetX10Response(values) ]++;
			break;
		default:
			return false;
	}
	timeout = 0;
	modbus.InitResponse();
	return true;
}
unsigned ModbusService::GetX01Response(list<VarOperator>& idlist)
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
		VarOperator r(slave, fcode, (offset + i), data);
		idlist.push_back(r);
	}

	return (idlist.begin() != idlist.end());
}
unsigned ModbusService::GetX02Response(list<VarOperator>& idlist)
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
		VarOperator r(slave, fcode, (offset + i), data);
		idlist.push_back(r);
	}

	return (idlist.begin() != idlist.end());
}
unsigned ModbusService::GetX03Response(list<VarOperator>& idlist)
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
		VarOperator r(slave, fcode, (offset + i), data);
		idlist.push_back(r);
	}

	return VarOperator(slave, fcode, offset, count).GetKey();
}
unsigned ModbusService::GetX04Response(list<VarOperator>& idlist)
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
		idlist.push_back(VarOperator(slave, fcode, (offset + i), data));
	}

	return VarOperator(slave, fcode, offset, count).GetKey();
}
unsigned ModbusService::GetX05Response(list<VarOperator>& idlist)
{
	X05Request &x = modbus.GetContext().GetX05Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int value = x.GetValue();

	idlist.clear();

	return (idlist.begin() != idlist.end());
}
unsigned ModbusService::GetX06Response(list<VarOperator>& idlist)
{
	X06Request &x = modbus.GetContext().GetX06Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int value = x.GetValue();

	idlist.clear();

	return (idlist.begin() != idlist.end());
}
unsigned ModbusService::GetX0fResponse(list<VarOperator>& idlist)
{
	X0fRequest &x = modbus.GetContext().GetX0fRequest();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int bcount = x.GetBcount();

	idlist.clear();

	return (idlist.begin() != idlist.end());
}
unsigned ModbusService::GetX10Response(list<VarOperator>& idlist)
{
	X10Request &x = modbus.GetContext().GetX10Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int bcount = x.GetBcount();

	idlist.clear();

	return (idlist.begin() != idlist.end());
}
map<unsigned,unsigned>& ModbusService::GetVarConfig(void)
{
	return requestmap;
}
