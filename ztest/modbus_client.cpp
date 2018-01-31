#include <stdio.h>
#include <unistd.h>
#include "service.h"
#include "modbusconfig.h"
#include "modbusmanager.h"


int main(void)
{
	Service client;
	string client_path = ".modbus.client";
	string server_path = ".modbus.service";

	ComConfig comconfig(1, 9600, 0, 8, 1);
	VarConfig varconfig(1, VarCmdAdd, 1, 3, 0, 9);
	VarName varname1(1, 0x01, 0x03, 0x0000, "1IN1");
	VarName varname2(1, 0x01, 0x03, 0x0001, "1IN2");
	VarName varname3(1, 0x01, 0x03, 0x0002, "1IN3");
	VarName varname4(1, 0x01, 0x03, 0x0003, "1IN4");
	VarName varname5(1, 0x01, 0x03, 0x0004, "1IN5");
	VarName varname6(1, 0x01, 0x03, 0x0005, "1IN6");
	VarName varname7(1, 0x01, 0x03, 0x0006, "1IN7");
	VarName varname8(1, 0x01, 0x03, 0x0007, "1IN8");
	VarName varname9(1, 0x01, 0x03, 0x0008, "1IN9");
                                                                              
	if( client.StartServer(client_path) == false )
	{
		printf("StartServer(%s) failed\n", client_path.data());
		return -1;
	}
	ModbusConfig mconfig;
	ComConfig& cm = mconfig.GetComConfig();
	VarConfig& vc = mconfig.GetVarConfig();
	VarName& vn = mconfig.GetVarName();

	getchar();
	cm = comconfig;
	mconfig.SetPacketType(TypeComConfig);
	client.SendPacket(server_path, mconfig.data(), mconfig.length());

	getchar();
	vc = varconfig;
	mconfig.SetPacketType(TypeVarConfig);
	client.SendPacket(server_path, mconfig.data(), mconfig.length());

	getchar();
	vn = varname1;
	mconfig.SetPacketType(TypeVarName);
	client.SendPacket(server_path, mconfig.data(), mconfig.length());

	getchar();
	vn = varname2;
	mconfig.SetPacketType(TypeVarName);
	client.SendPacket(server_path, mconfig.data(), mconfig.length());

	getchar();
	vn = varname3;
	mconfig.SetPacketType(TypeVarName);
	client.SendPacket(server_path, mconfig.data(), mconfig.length());

	getchar();
	vn = varname4;
	mconfig.SetPacketType(TypeVarName);
	client.SendPacket(server_path, mconfig.data(), mconfig.length());
	getchar();

	vn = varname5;
	mconfig.SetPacketType(TypeVarName);
	client.SendPacket(server_path, mconfig.data(), mconfig.length());

	getchar();
	vn = varname6;
	mconfig.SetPacketType(TypeVarName);
	client.SendPacket(server_path, mconfig.data(), mconfig.length());

	getchar();
	vn = varname7;
	mconfig.SetPacketType(TypeVarName);
	client.SendPacket(server_path, mconfig.data(), mconfig.length());

	getchar();
	vn = varname8;
	mconfig.SetPacketType(TypeVarName);
	client.SendPacket(server_path, mconfig.data(), mconfig.length());

	getchar();
	vn = varname9;
	mconfig.SetPacketType(TypeVarName);
	client.SendPacket(server_path, mconfig.data(), mconfig.length());

	return 0;
}
