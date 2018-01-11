#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "unix-udp.h"

UnixUdp::UnixUdp(void):sock(-1)
{
}
UnixUdp::UnixUdp(const string& path):sock(-1)
{
	if( Open() )
	{
		Bind(path);
	}
}
UnixUdp::~UnixUdp(void)
{
	Close();
	Unlink(m_path);
}
bool UnixUdp::Open(void)
{
	sock = socket(AF_UNIX, SOCK_DGRAM, 0);
	if( -1 == sock )
	{
		return false;
	}
	return true;
}
bool UnixUdp::Bind(const string& path)
{
	int len = path.length();
	if( len < 1 || len > 255 )
	{
		return false;
	}
	struct sockaddr_un sa = {AF_UNIX, 0};
	strncpy(sa.sun_path, path.data(), sizeof(sa.sun_path)-1);
	len = bind(sock, (struct sockaddr*)&sa, sizeof(sa.sun_family)+len);
	if(0 == len);
	{
		m_path = path;
		return true;
	}
	return false;
}
bool UnixUdp::Unlink(const string& path)
{
	if( path.empty() )
	{
		return false;
	}
	return (unlink(path.data()) == 0);
}
bool UnixUdp::Connect(const string& path)
{
	int len = path.length();
	if( len < 1 || len > 255 )
	{
		return false;
	}
	struct sockaddr_un sa = {AF_UNIX, 0};
	strncpy(sa.sun_path, path.data(), sizeof(sa.sun_path)-1);
	len = connect(sock, (struct sockaddr*)&sa, sizeof(sa.sun_family)+len);
	return (0 == len);
}
int UnixUdp::Recv(char *buf, int len)
{
	if( NULL == buf )
	{
		return 0;
	}
	if( len < 1 )
	{
		return 0;
	}
	return recv(sock, buf, len , 0);
}
int UnixUdp::Send(const char *buf, int len)
{
	if( NULL == buf )
	{
		return 0;
	}
	if( len < 1 )
	{
		return 0;
	}
	return send(sock, buf, len , 0);
}
int UnixUdp::SendTo(const string& path, const char *buf, int len)
{
	if( NULL == buf )
	{
		return 0;
	}
	if( len < 1 )
	{
		return 0;
	}
	int l = path.length();
	if( l < 1 || l > 255 )
	{
		return false;
	}
	struct sockaddr_un sa = {AF_UNIX, 0};
	strncpy(sa.sun_path, path.data(), sizeof(sa.sun_path)-1);
	return sendto(sock, buf, len , 0, (struct sockaddr*)&sa, sizeof(sa.sun_family)+l);
}
int UnixUdp::RecvFrom(string& path, char *buf, int len)
{
	if( NULL == buf )
	{
		return 0;
	}
	if( len < 1 )
	{
		return 0;
	}
	struct sockaddr_un sa = {0, 0};
	socklen_t slen = sizeof(struct sockaddr_un);
	int l = recvfrom(sock, buf, len, 0, (struct sockaddr*)&sa, &slen);
	if( l > 0 )
	{
		path = (sa.sun_family == AF_UNIX) ? sa.sun_path : "AF_UNSPEC";
		return l;
	}
	return 0;
}
bool UnixUdp::Block(void)
{
	return (fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) & ~O_NONBLOCK) == 0);
}
bool UnixUdp::Unblock(void)
{
	return (fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK) == 0);
}
bool UnixUdp::Close(void)
{
	shutdown(sock, SHUT_RDWR);
	return (close(sock) == 0);
}
