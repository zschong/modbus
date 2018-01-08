#ifndef __COMPORT_H__
#define __COMPORT_H__ 
#include <string>
#include "uart.h"
using namespace std;

class ComPort
{
private:
	int fd;
public:
	ComPort(void):fd(-1){}
public:
	bool Close(void);
	bool Block(bool b);
	bool Open(const string& path);
	bool Config(int baud, char parity, int bsize, int stop);
	virtual int  Recv(unsigned char *buf, int len);
	virtual int  Send(unsigned char *data, int len);
};

#endif//__COMPORT_H__
