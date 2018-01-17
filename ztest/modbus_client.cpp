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

	ComConfig comconfig("/dev/ttySX0", 9600, 0, 8, 1);
	VarConfig varconfig("/dev/ttySX0", VarCmdAdd, 1, 3, 0, 9, 80);
	VarName varname1("/dev/ttySX0", "1IN1", 0x01, 0x03, 0x0000);
	VarName varname2("/dev/ttySX0", "1IN2", 0x01, 0x03, 0x0001);
	VarName varname3("/dev/ttySX0", "1IN3", 0x01, 0x03, 0x0002);
	VarName varname4("/dev/ttySX0", "1IN4", 0x01, 0x03, 0x0003);
	VarName varname5("/dev/ttySX0", "1IN5", 0x01, 0x03, 0x0004);
	VarName varname6("/dev/ttySX0", "1IN6", 0x01, 0x03, 0x0005);
	VarName varname7("/dev/ttySX0", "1IN7", 0x01, 0x03, 0x0006);
	VarName varname8("/dev/ttySX0", "1IN8", 0x01, 0x03, 0x0007);
	VarName varname9("/dev/ttySX0", "1IN9", 0x01, 0x03, 0x0008);
                                                                              
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
