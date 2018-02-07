#include <stdio.h>
#include "modbusconfig.h"
#include "countfile.h"
#include "service.h"
#include "cgi.h"

string serverpath = "/home/user/var/.modbus.service";
string clientpath = "/home/user/var/.modbus.varconfig";

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

	mconfig.SetType( COM_CONFIG );
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

	mconfig.SetType( VAR_CONFIG );
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

	mconfig.SetType( VAR_CONFIG );
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
int getdata(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;

	int comid = cgi["comid"].toint();
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();
	map<unsigned,map<unsigned,VarOperator> > m;
	map<unsigned,map<unsigned,VarOperator> >::iterator A;
	map<unsigned,VarOperator>::iterator B;

	char buf[128];
	FILE *fp = fopen("var/data", "r");

	if( NULL == fp )
	{
		printf("{\"success\":false}");
		return 0;
	}
	while( fgets(buf, sizeof(buf)-1, fp) )
	{
		unsigned varid = 0;
		unsigned comid = 0;
		unsigned slave = 0;
		unsigned fcode = 0;
		unsigned offset= 0;
		unsigned value = 0;
		unsigned update = 0;
		sscanf(buf, "%u,%u,%u,%u,%u,%u,%u",
				&comid,
				&varid,
				&slave,
				&fcode,
				&offset,
				&value,
				&update
			  );
		VarOperator x(slave, fcode, offset, value, update);
		m[comid][x.GetKey()] = x;
	}
	fclose(fp);

	printf("{\"\":\"\",\"list\":[");
	for(A = m.begin(); A != m.end(); A++)
	{
		if( 0 != comid && A->first != comid )
		{
			continue;
		}
		for(B = A->second.begin(); B != A->second.end(); B++)
		{
			if( 0 != slave && slave != B->second.GetSlave() )
			{
				continue;
			}
			if( 0 != fcode && fcode != B->second.GetFcode() )
			{
				continue;
			}
			printf("{"
					"\"comid\":\"%u\""
					","
					"\"varid\":\"%08X\""
					","
					"\"slave\":\"%u\""
					","
					"\"fcode\":\"%u\""
					","
					"\"offset\":\"%05u\""
					","
					"\"value\":\"%u\""
					","
					"\"update\":\"%u\""
					"},",
					A->first,
					B->second.GetKey(),
					B->second.GetSlave(),
					B->second.GetFcode(),
					B->second.GetOffset(),
					B->second.GetCount(),
					B->second.GetInterval()
					);
		}
	}
	printf("{}]}");

	return -1;
}
int delvar(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;

	int comid = cgi["comid"].toint();
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();
	int offset= cgi["offset"].toint();
	int count = cgi["count"].toint();
	VarOperator x(slave, fcode, offset, count);

	mconfig.SetType( VAR_CONFIG );
	mconfig.GetVarConfig() = VarConfig(comid, VarCmdDel, x);

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

	mconfig.SetType( VAR_NAME );
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
int getcount(Cgi& cgi)
{
	Service service;
	ModbusConfig mconfig;

	int comid = cgi["comid"].toint();
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();
	map<unsigned,map<unsigned,SendRecvCount> > m;
	map<unsigned,map<unsigned,SendRecvCount> >::iterator A;
	map<unsigned,SendRecvCount>::iterator B;

	char buf[128];
	FILE *fp = fopen("var/count", "r");

	if( NULL == fp )
	{
		printf("{\"success\":false}");
		return 0;
	}
	while( fgets(buf, sizeof(buf)-1, fp) )
	{
		unsigned comid = 0;
		unsigned slave = 0;
		unsigned fcode = 0;
		unsigned offset= 0;
		unsigned count = 0;
		unsigned send = 0;
		unsigned recv = 0;
		sscanf(buf, "%u,%u,%u,%u,%u,%u,%u",
				&comid,
				&slave,
				&fcode,
				&offset,
				&count,
				&send,
				&recv
			  );
		VarOperator x(slave, fcode, offset, count);
		SendRecvCount &c = m[comid][x.GetKey()];
		c.slave = slave;
		c.fcode = fcode;
		c.offset= offset;
		c.count = count;
		c.send  = send;
		c.recv  = recv;
	}
	fclose(fp);

	printf("{\"\":\"\",\"list\":[");
	for(A = m.begin(); A != m.end(); A++)
	{
		if( 0 != comid && A->first != comid )
		{
			continue;
		}
		for(B = A->second.begin(); B != A->second.end(); B++)
		{
			if( 0 != slave && slave != B->second.slave )
			{
				continue;
			}
			if( 0 != fcode && fcode != B->second.fcode )
			{
				continue;
			}
			printf("{"
					"\"comid\":\"%u\""
					","
					"\"slave\":\"%u\""
					","
					"\"fcode\":\"%u\""
					","
					"\"offset\":\"%u\""
					","
					"\"count\":\"%u\""
					","
					"\"sendcount\":\"%u\""
					","
					"\"recvcount\":\"%u\""
					"},",
					A->first,
					B->second.slave,
					B->second.fcode,
					B->second.offset,
					B->second.count,
					B->second.send,
					B->second.recv
					);
		}
	}
	printf("{}]}");

	return -1;
}

int main(void)
{
	Cgi cgi;
	string cmd = cgi["cmd"];
	map<string,int(*)(Cgi&)> cmdmap;

	printf("Content-Type:text/json\r\n");
	printf("\r\n");

	cmdmap["login"] = login;
	cmdmap["setcom"] = setcom;
	cmdmap["addvar"] = addvar;
	cmdmap["setvar"] = setvar;
	cmdmap["delvar"] = delvar;
	cmdmap["namevar"] = namevar;
	cmdmap["config"] = getconfig;
	cmdmap["getcount"] = getcount;
	cmdmap["getdata"] = getdata;

	map<string,int(*)(Cgi&)>::iterator i = cmdmap.find(cmd);

	if( cmdmap.end() == i )
	{
		printf("{\"success\":\"false\",\"msg\":\"unknow cmd type!\"}");
		return 0;
	}
	if( i->second )
	{
		i->second(cgi);
	}

	return 0;
}
