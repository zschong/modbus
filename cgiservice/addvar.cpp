#include <stdio.h>
#include "addvar.h"

AddVar::AddVar(Cgi& cgi, const string& serverpath, const string& clientpath)
{
	Service service;
	ModbusConfig mconfig;

	int comid = cgi["comid"].toint();
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();
	int offset = cgi["offset"].toint();
	int count = cgi["count"].toint();
	int value = cgi["value"].toint();

	mconfig.SetType( VAR_CONFIG );
	VarConfig var(comid, VarCmdAdd, slave, fcode, offset, count);

	switch(fcode)
	{
		case 1:
		case 2:
		case 3:
		case 4:
			var.SetCommand(VarCmdAdd);
			break;
		case 5:
		case 6:
		case 15:
		case 16:
			var.SetCount(value);
			var.SetCommand(VarCmdSet);
			break;
		default:
			printf("{\"success\":\"true\",\"msg\":\"ok\"}");
			return;
	}
	mconfig.GetVarConfig() = var;

	if( service.StartServer(clientpath) == false )
	{
		printf("{\"success\":\"false\",\"msg\":\"connection failed\"}");
		return;
	}
	service.SendPacket(serverpath, mconfig.data(), mconfig.length());
	printf("{\"success\":\"true\",\"msg\":\"ok\"}");
}
