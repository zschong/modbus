#ifndef __MODBUS_H__
#define __MODBUS_H__
#include <string>
#include "comport.h"
#include "mcontext.h"
using namespace std;

class Modbus
{
protected:
	ComPort com;

public:
	Modbus(void);
	~Modbus(void);

public:
	bool Init(const string& dev, int baud, int parity, int bsize, int stop);

public:
	bool RecvRequest(Mcontext&);
	bool RecvResponse(Mcontext&);
	bool SendRequest(Mcontext&);
	bool SendResponse(Mcontext&);
};

#endif//__MODBUS_H__
