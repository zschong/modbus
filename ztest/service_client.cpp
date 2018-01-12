#include <stdio.h>
#include <unistd.h>
#include "service.h"
#include "timeoperator.h"

int main(int argc, char **argv)
{
	Service service;
	string client = ".test.service.unix.udp.client";
	string server = ".test.service.unix.udp.server";

	if( service.StartServer(client) == false )
	{
		printf("service.StartServer() failed!\n");
		return -1;
	}
	while(1)
	{
		service.SendPacket(server, (uint8_t*)server.data(), server.length());
		sleep(1);
	}
}
