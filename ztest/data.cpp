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
	int cid = cgi["cid"].toint();
	int baud = cgi["baud"].toint();
	int data = cgi["data"].toint();
	int stop = cgi["stop"].toint();
	int parity = cgi["parity"].toint();

	char buf[128];
	mconfig.SetPacketType(TypeComConfig);
	mconfig.GetComConfig() = ComConfig(cid, baud, parity, data, stop);

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

	int cid = cgi["cid"].toint();
	int did = cgi["did"].toint();
	int func = cgi["func"].toint();
	int vid = cgi["vid"].toint();
	int len = cgi["len"].toint();

	char buf[128];
	mconfig.SetPacketType(TypeVarConfig);
	mconfig.GetVarConfig() = VarConfig(cid, VarCmdAdd, did, func, vid, len);

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
	IdCount id(cgi["id"].xtoint(), 0);

	id.SetCount(1);
	mconfig.SetPacketType(TypeVarConfig);
	mconfig.GetVarConfig() = VarConfig(comid, VarCmdDel, id);

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
		fclose(fp);
		return -2;
	}
	fclose(fp);
	buf[sizeof(buf)-1] = 0;
	printf("%s", buf);

	return 0;
}
