#include <stdio.h>
#include "getconfig.h"
#include "getcount.h"
#include "getdata.h"
#include "setname.h"
#include "setcom.h"
#include "setvar.h"
#include "addvar.h"
#include "delvar.h"

string serverpath = "/home/user/var/.modbus.service";
string clientpath = "/home/user/var/.modbus.varconfig";

int login(Cgi& cgi)
{
	printf("{\"success\":\"true\",\"session\":\"123456789\"}");
	return 0;
}
int setcom(Cgi& cgi)
{
	SetCom x(cgi, serverpath, clientpath);
}
int addvar(Cgi& cgi)
{
	AddVar x(cgi, serverpath, clientpath);
}
int setvar(Cgi& cgi)
{
	SetVar x(cgi, serverpath, clientpath);
}
int getdata(Cgi& cgi)
{
	GetData x(cgi, serverpath, clientpath);
}
int delvar(Cgi& cgi)
{
	DelVar x(cgi, serverpath, clientpath);
}
int namevar(Cgi& cgi)
{
	SetName x(cgi, serverpath, clientpath);
}
int getconfig(Cgi& cgi)
{
	GetConfig x(cgi, serverpath, clientpath);
}
int getcount(Cgi& cgi)
{
	GetCount x(cgi, serverpath, clientpath);
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
