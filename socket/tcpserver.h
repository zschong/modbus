#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__
#include "xstring.h"
#include "tcp-socket.h"

class TcpServer
{
protected:
	int socket;

public:
	TcpServer(void);

public:
	bool Open(void);
	bool KeepAlive(int keep, int idle, int intervel, int count);
	int  Send(char *buf, int len);
	int  Recv(char *buf, int len);
	bool Block(void);
	bool Unblock(void);
	int  State(void);
	bool Close(void);
};

#endif//__TCP_SERVER_H__
