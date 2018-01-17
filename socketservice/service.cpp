#include <stdio.h>
#include "service.h"

Service::Service(void)
{
	length = 0;
}
void Service::ShowHex(void)
{
	for(int i = 0; i < length; i++)
	{
		printf("%02X ", buffer[i]);
		if( (i + 1 ) % 16 == 0 )
		{
			printf("\n");
		}
	}
	if( length > 0 )
	{
		printf("\n");
	}
}
int Service::GetLength(void)
{
	return length;
}
uint8_t* Service::GetData(void)
{
	return buffer;
}
bool Service::RecvPacket(void)
{
	length = server.RecvFrom(peer, (char*)buffer, sizeof(buffer));
	return (length > 0);
}
bool Service::SendPacket(const string& to, const char *data, int len)
{
	return SendPacket(to, (const uint8_t*)data, len);
}
bool Service::SendPacket(const string& to, const uint8_t *data, int len)
{
	if( NULL == data || len < 1 )
	{
		return false;
	}
	return (server.SendTo(to, (char*)data, len) == len);
}
bool Service::StartServer(const string& path)
{
	if( server.Open() == false )
	{
		return false;
	}
	if( server.Connect(path) )
	{
		return false;
	}
	server.Unlink(path);
	if( server.Bind(path) == false )
	{
		return false;
	}
	return server.Unblock();
}

#ifdef TEST_SERVICE
int main(int argc, char **argv)
{
	Service service;
	string serverpath = ".test.service.server";

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
#endif//TEST_SERVICE
