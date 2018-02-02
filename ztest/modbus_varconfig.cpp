#include <stdio.h>
#include "modbusconfig.h"
#include "service.h"
#include "cgi.h"

string serverpath = "/home/user/var/.modbus.service";
string clientpath = "/home/user/var/.modbus.varconfig";

int Login(Cgi& cgi);
int SetCom(Cgi& cgi);
int AddVar(Cgi& cgi);
int DelVar(Cgi& cgi);
int BindVar(Cgi& cgi);
int GetConfig(Cgi& cgi);

int main(void)
{
	Cgi cgi;
	string cmd = cgi["cmd"];

	printf("Content-Type:text/json\r\n");
	printf("\r\n");
	printf("\r\n");

	if( "login" == cmd )
	{
		Login(cgi);
	}
	else if( "setcom" == cmd )
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
	else if( "config" == cmd )
	{
		GetConfig(cgi);
	}

	return 0;
}

int Login(Cgi& cgi)
{
	printf("{\"success\":\"true\",\"session\":\"123456789\"}");
	return 0;
}

int SetCom(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;
	int comid = cgi["com"].toint();
	int baud = cgi["baud"].toint();
	int parity = cgi["parity"].toint();
	int bsize = cgi["bsize"].toint();
	int stop = cgi["stop"].toint();

	mconfig.SetPacketType(TypeComConfig);
	mconfig.GetComConfig() = ComConfig(comid, baud, parity, bsize, stop);

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

	int comid = cgi["com"].toint();
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();
	int offset = cgi["offset"].toint();
	int count = cgi["count"].toint();

	mconfig.SetPacketType(TypeVarConfig);
	mconfig.GetVarConfig() = VarConfig(comid, VarCmdAdd, slave, fcode, offset, count);

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

	int comid = cgi["com"].toint();
	RegisterOperator roperator(cgi["id"].xtoint(), (1 << 16));

	mconfig.SetPacketType(TypeVarConfig);
	mconfig.GetVarConfig() = VarConfig(comid, VarCmdDel, roperator);

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
	int comid = cgi["com"].toint();
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();
	int offset = cgi["offset"].toint();
	string name = cgi["name"];

	mconfig.SetPacketType(TypeVarName);
	mconfig.GetVarName() = VarName(comid, slave, fcode, offset, name);

	if( service.StartServer(clientpath) == false )
	{
		printf("{\"success\":\"false\",\"msg\":\"connection failed\"}");
		return -1;
	}
	service.SendPacket(serverpath, mconfig.data(), mconfig.length());
	printf("{\"success\":\"true\",\"msg\":\"ok\"}");
	return 0;
}
int GetConfig(Cgi& cgi)
{
	char buf[4096] = {0};
	FILE *fp = fopen("com.config", "r");

	if( NULL == fp )
	{
		return -1;
	}
	if( fread(buf, 1, sizeof(buf), fp) < 1 )
	{
		return -2;
	}
	buf[sizeof(buf)-1] = 0;
	printf("%s", buf);

	return 0;
}
