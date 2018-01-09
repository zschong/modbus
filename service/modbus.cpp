#include <time.h>
#include "modbus.h"
#include "timeoperator.h"

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
bool Modbus::RecvRequest(Mcontext& context)
{
	unsigned char c = 0;

	if( com.Recv(&c, 1) == 1 )
	{
		context.Push(c);
	}
	return (context.CheckRequest() == 1);
}
bool Modbus::RecvResponse(Mcontext& context)
{
	unsigned char c = 0;

	if( com.Recv(&c, 1) == 1 )
	{
		context.Push(c);
	}
	return (context.CheckResponse() == 1);
}
bool Modbus::SendRequest(Mcontext& context)
{
	return (com.Send(context.GetData(), context.GetLength()) == context.GetLength());
}
bool Modbus::SendResponse(Mcontext& context)
{
	return (com.Send(context.GetData(), context.GetLength()) == context.GetLength());
}

#ifdef TEST_MODBUS
int main(int argc, char **argv)
{
	Modbus modbus;
	Mcontext context1;
	Mcontext context2;
	X03Request &x03req = context1.GetX03Request();
	X03Response &x03res = context2.GetX03Response();
	string comdev = "/dev/ttySX0";

	if( modbus.Init(comdev, 9600, 0, 8, 1) == false )
	{
		printf("modbus.Init failed!\n");
		return -1;
	}

	uint16_t count = 1;
	TimeOperator timer;

	while(1)
	{
		if( timer.sdiff() != 0 )
		{
			x03res.SetMaster(1);
			x03req.SetSlave(0x01);
			x03req.SetFcode(0x03);
			x03req.SetOffset(0x0000);
			x03req.SetCount(count++);
			x03req.SetCrc( x03req.CalcCrc() );
			modbus.SendRequest(x03req);
			timer.init();
			printf("send:");
			x03req.Show();
			if( count > 15 )
			{
				count = 1;
			}
		}
		if( modbus.RecvResponse(x03res) )
		{
			printf("T{%d}recv:", timer.mdiff());
			x03res.Show();
			x03res.Init();
		}
		usleep(100);
	}

	return 0;
}
#endif//TEST_MODBUS
