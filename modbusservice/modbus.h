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
	X01Request x01request;
	X02Request x02request;
	X03Request x03request;
	X04Request x04request;
	X05Request x05request;
	X06Request x06request;
	X0fRequest x0frequest;
	X10Request x10request;

	X01Response x01response;
	X02Response x02response;
	X03Response x03response;
	X04Response x04response;
	X05Response x05response;
	X06Response x06response;
	X0fResponse x0fresponse;
	X10Response x10response;

public:
	Modbus(void);
	~Modbus(void);

public:
	bool Init(const string& dev, int baud, int parity, int bsize, int stop);

public:
	void InitRequest(void);
	void InitResponse(void);
	uint8_t RecvRequest(void);
	uint8_t RecvResponse(void);
	bool RecvRequest(Mcontext&);
	bool RecvResponse(Mcontext&);
	bool SendRequest(Mcontext&);
	bool SendResponse(Mcontext&);
public:
	void RequestShow(uint8_t);
	void ResponseShow(uint8_t);
};

#endif//__MODBUS_H__
