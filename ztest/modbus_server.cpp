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
					{
					packet.GetVarConfig().Show();
					manager.SetVarConfig( packet.GetVarConfig() );
					map<unsigned,map<unsigned,unsigned> > mmu;
					manager.GetVarConfig(mmu);
					break;
					}
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
