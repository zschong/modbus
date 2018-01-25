#include <stdio.h>
#include "modbusconfig.h"
#include "service.h"
#include "cgi.h"

string serverpath = "/home/user/var/.modbus.service";
string clientpath = "/home/user/var/.modbus.varconfig";

int SetCom(Cgi& cgi);
int AddVar(Cgi& cgi);
int DelVar(Cgi& cgi);
int BindVar(Cgi& cgi);

int main(void)
{
	Cgi cgi;
	string cmd = cgi["cmd"];

	printf("Content-Type:text/html\r\n");
	printf("\r\n\r\nok\n");

	if( "setcom" == cmd )
	{
		SetCom(cgi);
	}
	else if( "addvar" == cmd )
	{
		AddVar(cgi);
	}
	else if( "delvar" == cmd )
	{
		DelVar(cgi);
	}
	else if( "bindvar" == cmd )
	{
		BindVar(cgi);
	}


	return 0;
}

int SetCom(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;
	const string com = cgi["com"];
	int baud = cgi["baud"].toint();
	int parity = cgi["parity"].toint();
	int bsize = cgi["bsize"].toint();
	int stop = cgi["stop"].toint();

	mconfig.SetPacketType(TypeComConfig);
	//mconfig.GetComConfig() = ComConfig(com, 9600, 0, 8, 1);
	mconfig.GetComConfig() = ComConfig(com, baud, parity, bsize, stop);

	if( service.StartServer(clientpath) == false )
	{
		printf("failed start(%s)\n", clientpath.data());
		return 0;
	}
	return service.SendPacket(serverpath, mconfig.data(), mconfig.length());
}
int AddVar(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;

	string com = cgi["com"];
	string name = cgi["name"];
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();
	int offset = cgi["offset"].toint();
	int count = cgi["count"].toint();
	int interval = cgi["interval"].toint();


	if( service.StartServer(clientpath) == false )
	{
		printf("failed start(%s)\n", clientpath.data());
		return 0;
	}

	mconfig.SetPacketType(TypeVarConfig);
	mconfig.GetVarConfig() = VarConfig(com, VarCmdAdd, slave, fcode, offset, count, interval);

	return service.SendPacket(serverpath, mconfig.data(), mconfig.length());
}
int DelVar(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;

	string com = cgi["com"];
	IdCount id(cgi["id"].xtoint(), 0);

	if( service.StartServer(clientpath) == false )
	{
		printf("failed start(%s)\n", clientpath.data());
		return 0;
	}
	printf("id=%s=%08X, <%08X, %08X>\n", cgi["id"].data(), cgi["id"].xtoint(), id.GetKey(), id.GetValue());

	id.SetCount(1);
	mconfig.SetPacketType(TypeVarConfig);
	mconfig.GetVarConfig() = VarConfig(com, VarCmdDel, id);

	return service.SendPacket(serverpath, mconfig.data(), mconfig.length());
}
int BindVar(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;
	string com = cgi["com"];
	string name = cgi["name"];
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();
	int offset = cgi["offset"].toint();
	int count = cgi["count"].toint();
	int interval = cgi["interval"].toint();

	mconfig.SetPacketType(TypeVarName);
	mconfig.GetVarName() = VarName(com, name, slave, fcode, offset);

	return service.SendPacket(serverpath, mconfig.data(), mconfig.length());
}
