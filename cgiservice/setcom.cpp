#include <stdio.h>
#include "setcom.h"

SetCom::SetCom(Cgi& cgi, const string& serverpath, const string& clientpath)
{
	Service service;
	ModbusConfig mconfig;
	int comid  = cgi["comid"].toint();
	int baud   = cgi["baud"].toint();
	int parity = cgi["parity"].toint();
	int bsize  = cgi["bsize"].toint();
	int stop   = cgi["stop"].toint();

	mconfig.SetType( COM_CONFIG );
	mconfig.GetComConfig() = ComConfig(comid, baud, parity, bsize, stop);

	if( service.StartServer(clientpath) == false )
	{
		printf("{\"success\":\"false\",\"msg\":\"connection failed\"}");
		return;
	}
	service.SendPacket(serverpath, mconfig.data(), mconfig.length());
	printf("{\"success\":\"true\",\"msg\":\"ok\"}");
}
