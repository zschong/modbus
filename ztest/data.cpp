#include <stdio.h>
#include "modbusconfig.h"
#include "service.h"
#include "cgi.h"

string serverpath = "/home/user/var/.modbus.service";
string clientpath = "/home/user/var/.modbus.varconfig";

int Login(Cgi& cgi);
int Logout(Cgi& cgi);
int SetCom(Cgi& cgi);
int AddVar(Cgi& cgi);
int DelVar(Cgi& cgi);
int BindVar(Cgi& cgi);

int main(void)
{
	Cgi cgi;
	string cmd = cgi["cmd"];

	printf("Content-Type:text/json\r\n");
	printf("\r\n");
	printf("\r\n");

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
	mconfig.GetComConfig() = ComConfig(com, baud, parity, bsize, stop);

	if( service.StartServer(clientpath) == false )
	{
		printf("{\"success\":\"false\",\"msg\":\"connection failed\"}");
		return -1;
	}
	service.SendPacket(serverpath, mconfig.data(), mconfig.length());
	printf("{\"success\":\"true\",\"msg\":\"ok\"}");
	return 0;
}
int AddVar(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;

	string com = cgi["com"];
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();
	int offset = cgi["offset"].toint();
	int count = cgi["count"].toint();
	int interval = cgi["interval"].toint();

	mconfig.SetPacketType(TypeVarConfig);
	mconfig.GetVarConfig() = VarConfig(com, VarCmdAdd, slave, fcode, offset, count, interval);

	if( service.StartServer(clientpath) == false )
	{
		printf("{\"success\":\"false\",\"msg\":\"connection failed\"}");
		return -1;
	}
	service.SendPacket(serverpath, mconfig.data(), mconfig.length());
	printf("{\"success\":\"true\",\"msg\":\"ok\"}");
	return 0;
}
int DelVar(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;

	string com = cgi["com"];
	IdCount id(cgi["id"].xtoint(), 0);

	id.SetCount(1);
	mconfig.SetPacketType(TypeVarConfig);
	mconfig.GetVarConfig() = VarConfig(com, VarCmdDel, id);

	if( service.StartServer(clientpath) == false )
	{
		printf("{\"success\":\"false\",\"msg\":\"connection failed\"}");
		return -1;
	}
	service.SendPacket(serverpath, mconfig.data(), mconfig.length());
	printf("{\"success\":\"true\",\"msg\":\"ok\"}");
	return 0;
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

	if( service.StartServer(clientpath) == false )
	{
		printf("{\"success\":\"false\",\"msg\":\"connection failed\"}");
		return -1;
	}
	service.SendPacket(serverpath, mconfig.data(), mconfig.length());
	printf("{\"success\":\"true\",\"msg\":\"ok\"}");
	return 0;
}
