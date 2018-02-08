#include <stdio.h>
#include "delvar.h"

DelVar::DelVar(Cgi& cgi, const string& serverpath, const string& clientpath)
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
		return;
	}
	service.SendPacket(serverpath, mconfig.data(), mconfig.length());
	printf("{\"success\":\"true\",\"msg\":\"ok\"}");
}
