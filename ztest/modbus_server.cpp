#include <stdio.h>
#include <unistd.h>
#include "service.h"
#include "valuefile.h"
#include "modbusconfig.h"
#include "modbusmanager.h"


void ShowValue(const Value& value)
{
	printf("[%s][%s][%08X][%04X][%-4d][t=%d]\n", 
			value.GetName().data(),
			value.GetCom().data(), 
			value.GetId(), 
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
	valuefile.SetComMap("/dev/ttySX", "COM");
                                                                              
	while(1)
	{
		if( service.RecvPacket() )
		{
			ModbusConfig &p = *(ModbusConfig*)service.GetData();
			switch(p.GetPacketType())
			{
				case TypeVarName:
					p.GetVarName().Show();
					manager.SetVarName( p.GetVarName() );
					break;
				case TypeVarConfig:
					p.GetVarConfig().Show();
					manager.SetVarConfig( p.GetVarConfig() );
					break;
				case TypeComConfig:
					p.GetComConfig().Show();
					manager.SetComConfig( p.GetComConfig() );
					break;
			}
		}
		manager.RunLoop();
		if( ftimer.mdiff() > 1017 )
		{
			map<string,map<int,Value> > mmv;
			manager.GetValue(mmv);
			valuefile.MakeFile(mmv);
			ftimer.init();
		}
		usleep(100);
	}

	return 0;
}
