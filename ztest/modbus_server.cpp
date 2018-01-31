#include <stdio.h>
#include <unistd.h>
#include "service.h"
#include "valuefile.h"
#include "modbusconfig.h"
#include "modbusmanager.h"


void ShowValue(const ModbusValue& value)
{
	printf("[%s][%d][%08X][%04X][%-4d][t=%d]\n", 
			value.GetVarName().data(),
			value.GetComId(), 
			value.GetVarId(), 
			value.GetValue(),
			value.GetValue(),
			value.mdiff());
}

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
	manager.SetComId("/dev/ttyS0", 0);
	manager.SetComId("/dev/ttyS1", 1);
	manager.SetComId("/dev/ttyS2", 2);
	manager.SetComId("/dev/ttyS3", 3);
	manager.SetComId("/dev/ttyS4", 4);
	manager.SetComId("/dev/ttyS5", 5);
	manager.SetComId("/dev/ttyS6", 6);
	manager.SetComId("/dev/ttyS7", 7);
	manager.SetComId("/dev/ttyS8", 8);
	valuefile.SetFileName("var/allcom.json");
                                                                              
	while(1)
	{
		if( service.RecvPacket() )
		{
			ModbusConfig &packet = *(ModbusConfig*)service.GetData();
			switch( packet.GetPacketType() )
			{
				case TypeVarName:
					packet.GetVarName().Show();
					manager.SetVarName( packet.GetVarName() );
					break;
				case TypeVarConfig:
					packet.GetVarConfig().Show();
					manager.SetVarConfig( packet.GetVarConfig() );
					break;
				case TypeComConfig:
					packet.GetComConfig().Show();
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
