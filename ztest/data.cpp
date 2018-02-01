#include <stdio.h>
#include "modbusconfig.h"
#include "service.h"
#include "cgi.h"

string serverpath = "/home/user/var/.modbus.service";
string clientpath = "/home/user/var/.modbus.varconfig";

int login(Cgi& cgi);
int setcom(Cgi& cgi);
int addvar(Cgi& cgi);
int setvar(Cgi& cgi);
int delvar(Cgi& cgi);
int getvar(Cgi& cgi);
int namevar(Cgi& cgi);
int getconfig(Cgi& cgi);

int main(void)
{
	Cgi cgi;
	string cmd = cgi["cmd"];

	printf("Content-Type:text/json\r\n");
	printf("\r\n");
	//printf("\r\n");

	if( "getvar" == cmd )
	{
		getvar(cgi);
	}
	else if( "login" == cmd )
	{
		login(cgi);
	}
	else if( "setcom" == cmd )
	{
		setcom(cgi);
	}
	else if( "addvar" == cmd )
	{
		addvar(cgi);
	}
	else if( "setvar" == cmd )
	{
		setvar(cgi);
	}
	else if( "delvar" == cmd )
	{
		delvar(cgi);
	}
	else if( "namevar" == cmd )
	{
		namevar(cgi);
	}
	else if( "config" == cmd )
	{
		getconfig(cgi);
	}

	return 0;
}

int login(Cgi& cgi)
{
	printf("{\"success\":\"true\",\"session\":\"123456789\"}");
	return 0;
}
int setcom(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;
	int comid = cgi["comid"].toint();
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
int addvar(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;

	int comid = cgi["comid"].toint();
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
int setvar(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;

	int comid = cgi["comid"].toint();
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();
	int offset = cgi["offset"].toint();
	int value = cgi["value"].toint();

	mconfig.SetPacketType(TypeVarConfig);
	mconfig.GetVarConfig() = VarConfig(comid, VarCmdSet, slave, fcode, offset, value);

	if( service.StartServer(clientpath) == false )
	{
		printf("{\"success\":\"false\",\"msg\":\"connection failed\"}");
		return -1;
	}
	service.SendPacket(serverpath, mconfig.data(), mconfig.length());
	printf("{\"success\":\"true\",\"msg\":\"ok\"}");
	return 0;
}
int getvar(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;

	int comid = cgi["comid"].toint();
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();

	char buf[128];
	FILE *fp = NULL;

	if( comid == 0 )
	{
		snprintf(buf, sizeof(buf), "var/allcom.json");
		fp = fopen(buf, "r");
	}
	else if( slave == 0 )
	{
		snprintf(buf, sizeof(buf), "var/COM%d.json", comid);
		fp = fopen(buf, "r");
	}
	else
	{
		snprintf(buf, sizeof(buf), "var/COM%d.%d.json", comid, slave);
		fp = fopen(buf, "r");
	}
	if( fp )
	{
		printf("{\"success\":true,\"list\":");
	}
	while(fp)
	{
		char data[1025] = {0};
		int len = fread(data, 1, 1024, fp);
		if( len > 0 )
		{
			data[len] = 0;
			printf("%s", data);
			continue;
		}
		printf("}");
		return 0;
	}
	printf("{\"success\":false}");

	return -1;
}
int delvar(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;

	int comid = cgi["comid"].toint();
	IdCount id(cgi["varid"].xtoint(), 1);

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
int namevar(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;
	int comid = cgi["comid"].toint();
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
int getconfig(Cgi& cgi)
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
