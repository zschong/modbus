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
			srcount[ x.GetKey() ] += 0x10000;
			break;
		case 0x02:
			SendX02Request(x);
			srcount[ x.GetKey() ] += 0x10000;
			break;
		case 0x03:
			SendX03Request(x);
			srcount[ x.GetKey() ] += 0x10000;
			break;
		case 0x04:
			SendX04Request(x);
			srcount[ x.GetKey() ] += 0x10000;
			break;
		case 0x05:
			SendX05Request(x);
			srcount[ x.GetKey() ] += 0x10000;
			break;
		case 0x06:
			SendX06Request(x);
			srcount[ x.GetKey() ] += 0x10000;
			break;
		case 0x0f:
			SendX0fRequest(x);
			srcount[ x.GetKey() ] += 0x10000;
			break;
		case 0x10:
			SendX10Request(x);
			srcount[ x.GetKey() ] += 0x10000;
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
			srcount[ GetX01Response(values) ]++;
			break;
		case 0x02:
			srcount[ GetX02Response(values) ]++;
			break;
		case 0x03:
			srcount[ GetX03Response(values) ]++;
			break;
		case 0x04:
			srcount[ GetX04Response(values) ]++;
			break;
		case 0x05:
			srcount[ GetX05Response(values) ]++;
			break;
		case 0x06:
			srcount[ GetX06Response(values) ]++;
			break;
		case 0x0f:
			srcount[ GetX0fResponse(values) ]++;
			break;
		case 0x10:
			srcount[ GetX10Response(values) ]++;
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

	return VarOperator(slave, fcode, offset, count).GetKey();
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

	return VarOperator(slave, fcode, offset, count).GetKey();
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

	return VarOperator(slave, fcode, offset, 1).GetKey();
}
unsigned ModbusService::GetX06Response(list<VarOperator>& idlist)
{
	X06Request &x = modbus.GetContext().GetX06Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int value = x.GetValue();

	idlist.clear();

	return VarOperator(slave, fcode, offset, 1).GetKey();
}
unsigned ModbusService::GetX0fResponse(list<VarOperator>& idlist)
{
	X0fRequest &x = modbus.GetContext().GetX0fRequest();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int count = x.GetCount();
	int bcount = x.GetBcount();

	idlist.clear();

	return VarOperator(slave, fcode, offset, count).GetKey();
}
unsigned ModbusService::GetX10Response(list<VarOperator>& idlist)
{
	X10Request &x = modbus.GetContext().GetX10Request();
	int slave = x.GetSlave();
	int fcode = x.GetFcode();
	int offset = x.GetOffset();
	int count = x.GetCount();
	int bcount = x.GetBcount();

	idlist.clear();

	return VarOperator(slave, fcode, offset, count).GetKey();
}
map<unsigned,unsigned>& ModbusService::GetVarConfig(void)
{
	return requestmap;
}
map<unsigned,SendRecvCount> ModbusService::GetCount(void)
{
	map<unsigned,SendRecvCount> countmap;
	map<unsigned,unsigned>::iterator i;

	for(i = requestmap.begin(); i != requestmap.end(); i++)
	{
		VarOperator x(i->first, i->second);
		SendRecvCount &c = countmap[i->first];
		unsigned sendrecv = srcount[i->first];

		c.slave = x.GetSlave();
		c.fcode = x.GetFcode();
		c.offset= x.GetOffset();
		c.count = x.GetCount();
		c.send = 0xffff & (sendrecv >> 16);
		c.recv = 0xffff & (sendrecv >>  0);
		if( c.send > 1000 || c.recv > 1000 )
		{
			//srcount[i->first] = 0;
		}
		if( c.send < c.recv )
		{
			c.recv = c.send = 0;
		}
	}
	return countmap;
}
