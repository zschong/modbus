#include <stdio.h>
#include <unistd.h>
#include "service.h"
#include "timeoperator.h"

int main(int argc, char **argv)
{
	Service service;
	string serverpath = ".test.service.unix.udp.server";

	if( service.StartServer(serverpath) == false )
	{
		printf("service.StartServer() failed!\n");
		return -1;
	}
	while(1)
	{
		if( service.RecvPacket() )
		{
			printf("%s\n", service.GetData());
			//service.ShowHex();
		}
		usleep(100);
	}
}
