#include <stdio.h>
#include "setvar.h"

SetVar::SetVar(Cgi& cgi, const string& serverpath, const string& clientpath)
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
		return;
	}
	service.SendPacket(serverpath, mconfig.data(), mconfig.length());
	printf("{\"success\":\"true\",\"msg\":\"ok\"}");
}
