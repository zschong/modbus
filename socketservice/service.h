#ifndef __SERVICE_H__
#define __SERVICE_H__
#include <map>
#include <string>
#include "packet.h"
#include "unix-udp.h"
using namespace std;

class Service
{
protected:
	int length;
	string peer;
	UnixUdp server;
	uint8_t buffer[4096];

public:
	Service(void);

public:
	bool RecvPacket(void);
	bool SendPacket(const string&, const char *data, int len);
	bool SendPacket(const string&, const uint8_t *data, int len);
	bool StartServer(const string& path);

public:
	void ShowHex(void);
	int GetLength(void);
	uint8_t* GetData(void);
};

#endif//__SERVICE_H__
