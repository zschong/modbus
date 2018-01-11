#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__
#include "xstring.h"
#include "tcp-socket.h"

class TcpClient
{
protected:
	int socket;

public:
	TcpClient(void);

public:
	bool Open(void);
	bool Connect(const xstring& ip, int port);
	bool KeepAlive(int keep, int idle, int intervel, int count);
	int  Send(char *buf, int len);
	int  Recv(char *buf, int len);
	bool Block(void);
	bool Unblock(void);
	int  State(void);
	bool Close(void);
};

#endif//__TCP_CLIENT_H__
