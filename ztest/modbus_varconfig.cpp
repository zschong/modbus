#include <stdio.h>
#include "cgi.h"
#include "service.h"
#include "modbusconfig.h"

int main(void)
{
	Cgi cgi;
	Service s;
	string sp = "/home/user/var/.modbus.service";
	string cp = "/home/user/var/.modbus.varconfig";
	string com = cgi["com"];
	string name = cgi["name"];
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();
	int offset = cgi["offset"].toint();
	int count = cgi["count"].toint();
	int interval = cgi["interval"].toint();


	ModbusConfig mc;
	VarName &vn = mc.GetVarName();
	VarConfig &vc = mc.GetVarConfig();
	ComConfig &cc = mc.GetComConfig();

	ComConfig ccfg(com, 9600, 0, 8, 1);
	VarConfig vcfg(com, VarCmdAdd, slave, fcode, offset, count, interval);
	VarName vname(com, name, slave, fcode, offset);

	if( s.StartServer(cp) == false )
	{
		printf("failed start(%s)\n", cp.data());
		return 0;
	}

	cc = ccfg;
	mc.SetPacketType(TypeComConfig);
	s.SendPacket(sp, mc.data(), mc.length());

	vc = vcfg;
	mc.SetPacketType(TypeVarConfig);
	s.SendPacket(sp, mc.data(), mc.length());

	vn = vname;
	mc.SetPacketType(TypeVarName);
	//s.SendPacket(sp, mc.data(), mc.length());

	printf("Content-Type:text/html\r\n");
	printf("\r\n\r\nok\n");

	return 0;
}
