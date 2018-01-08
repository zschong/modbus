#include "modbus.h"

Modbus::Modbus(void)
{

}
Modbus::~Modbus(void)
{
	com.Close();
}
bool Modbus::Init(const string& dev, int baud, int parity, int bsize, int stop)
{
	if( com.Close() == false )
	{
		return false;
	}
	if( com.Open(dev) == false )
	{
		return false;
	}
	if( com.Config(baud, parity, bsize, stop) == false )
	{
		return false;
	}
	if( com.Block(false) == false )
	{
		return false;
	}
	return true;
}
bool Modbus::GetRequest(Mcontext& context)
{
	unsigned char c = 0;

	if( com.Recv(&c, 1) == 1 )
	{
		context.Push(c);
	}
	return (context.CheckRequest() == 1);
}
bool Modbus::GetResponse(Mcontext& context)
{
	unsigned char c = 0;

	if( com.Recv(&c, 1) == 1 )
	{
		context.Push(c);
	}
	return (context.CheckResponse() == 1);
}
