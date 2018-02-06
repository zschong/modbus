#include <stdio.h>
#include <unistd.h>
#include "service.h"
#include "valuefile.h"
#include "modbusconfig.h"
#include "modbusmanager.h"


int main(void)
{
	Service service;
	ValueFile valuefile;
	TimeOperator timer;
	TimeOperator ftimer;
	ModbusManager manager;
	string server_path = "/home/user/var/.modbus.service";

	if( service.StartServer(server_path) == false )
	{
		printf("StartServer(%s) failed\n", server_path.data());
		return -1;
	}
	manager.LoadComId(".com.id");
	manager.LoadComConfig(".com.config");
	manager.LoadVarConfig(".var.config");
	valuefile.SetFileName("var/allcom.json");

	while(1)
	{
		if( service.RecvPacket() )
		{
			ModbusConfig &packet = *(ModbusConfig*)service.GetData();
			switch( packet.GetType() )
			{
				case VAR_NAME:
					manager.SetVarName( packet.GetVarName() );
					break;
				case VAR_CONFIG:
					manager.SetVarConfig( packet.GetVarConfig() );
					break;
				case COM_CONFIG:
					manager.SetComConfig( packet.GetComConfig() );
					break;
			}
		}
		manager.RunLoop();
		if( ftimer.mdiff() > 1017 )
		{
			map<unsigned,map<unsigned,ModbusValue> > mmv;
			manager.GetValue(mmv);
			valuefile.MakeFile(mmv);
			ftimer.init();
		}
		usleep(100);
	}

	return 0;
}
