#ifndef __UNIX_UDP_H__
#define __UNIX_UDP_H__
#include <string>
using namespace std;

class UnixUdp
{
protected:
	int sock;
	string m_path;
public:
	UnixUdp(void);
	UnixUdp(const string& path);
	~UnixUdp(void);
public:
	bool Open(void);
	bool Bind(const string& path);
	bool Unlink(const string& path);
	bool Connect(const string& path);
	int Recv(char *buf, int len);
	int Send(const char *buf, int len);
	int SendTo(const string& path, const char *buf, int len);
	int RecvFrom(string& path, char *buf, int len);
	bool Block(void);
	bool Unblock(void);
	bool Close(void);
public:
	const string& GetPath(void)const{return m_path;}
};


#endif//__UNIX_UDP_H__
