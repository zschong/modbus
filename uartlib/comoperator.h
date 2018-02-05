#ifndef __COM_OPERATOR_H__
#define __COM_OPERATOR_H__ 
#include <string>
#include "uart.h"
using namespace std;

class ComOperator
{
private:
	int comfd;
public:
	ComOperator(void);
public:
	bool Close(void);
	bool Block(bool b);
	bool Open(const string& path);
	bool Config(int baud, char parity, int bsize, int stop);
	virtual int  Recv(unsigned char *buf, int len);
	virtual int  Send(unsigned char *data, int len);
};

#endif//__COM_OPERATOR_H__
