#include "tcpclient.h"

TcpClient::TcpClient(void):socket(-1)
{
	//tcp client constructure
}
bool TcpClient::Open(void)
{
	if( -1 == socket )
	{
		socket = tcp_open(); 
	}
	return (-1 != socket);
}
bool TcpClient::Connect(const xstring& ip, int port)
{
	if( ip.empty() )
	{
		return false;
	}
	return (tcp_connects(socket, ip.data(), port) == 0);
}
bool TcpClient::KeepAlive(int keep, int idle, int intervel, int count)
{
	return tcp_keepalive(socket, keep, idle, intervel, count);
}
int  TcpClient::Send(char *buf, int len)
{
	return tcp_send(socket, buf, len);
}
int  TcpClient::Recv(char *buf, int len)
{
	return tcp_recv(socket, buf, len);
}
bool TcpClient::Block(void)
{
	return (tcp_block(socket) == 0);
}
bool TcpClient::Unblock(void)
{
	return (tcp_nonblock(socket) == 0);
}
int  TcpClient::State(void)
{
	return tcp_state(socket);
}
bool TcpClient::Close(void)
{
	return (tcp_close(socket) == 0);
}
