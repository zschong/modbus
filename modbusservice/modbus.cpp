#include <time.h>
#include "modbus.h"
#include "timeoperator.h"

Modbus::Modbus(void)
{
	InitRequest();
	InitResponse();
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
void Modbus::RequestShow(uint8_t i)
{
	switch(i)
	{
		case 0x01:
			return x01request.Show();
		case 0x02:
			return x02request.Show();
		case 0x03:
			return x03request.Show();
		case 0x04:
			return x04request.Show();
		case 0x05:
			return x05request.Show();
		case 0x06:
			return x06request.Show();
		case 0x0f:
			return x0frequest.Show();
		case 0x10:
			return x10request.Show();
	}
}
void Modbus::ResponseShow(uint8_t i)
{
	switch(i)
	{
		case 0x01:
			return x01response.Show();
		case 0x02:
			return x02response.Show();
		case 0x03:
			return x03response.Show();
		case 0x04:
			return x04response.Show();
		case 0x05:
			return x05response.Show();
		case 0x06:
			return x06response.Show();
		case 0x0f:
			return x0fresponse.Show();
		case 0x10:
			return x10response.Show();
	}
}
void Modbus::InitRequest(void)
{
	x01request.Init();
	x02request.Init();
	x03request.Init();
	x04request.Init();
	x05request.Init();
	x06request.Init();
	x0frequest.Init();
	x10request.Init();
}
void Modbus::InitResponse(void)
{
	x01response.Init();
	x02response.Init();
	x03response.Init();
	x04response.Init();
	x05response.Init();
	x06response.Init();
	x0fresponse.Init();
	x10response.Init();
}
uint8_t Modbus::RecvRequest(void)
{
	unsigned char c = 0;

	if( com.Recv(&c, 1) == 1 )
	{
		x01request.Push(c);
		x02request.Push(c);
		x03request.Push(c);
		x04request.Push(c);
		x05request.Push(c);
		x06request.Push(c);
		x0frequest.Push(c);
		x10request.Push(c);
	}
	if( x01request.CheckRequest() == 1 )
	{
		return 0x01;
	}
	if( x02request.CheckRequest() == 1 )
	{
		return 0x02;
	}
	if( x03request.CheckRequest() == 1 )
	{
		return 0x03;
	}
	if( x04request.CheckRequest() == 1 )
	{
		return 0x04;
	}
	if( x05request.CheckRequest() == 1 )
	{
		return 0x05;
	}
	if( x06request.CheckRequest() == 1 )
	{
		return 0x06;
	}
	if( x0frequest.CheckRequest() == 1 )
	{
		return 0x0f;
	}
	if( x10request.CheckRequest() == 1 )
	{
		return 0x10;
	}
	return 0;
}
uint8_t Modbus::RecvResponse(void)
{
	unsigned char c = 0;

	if( com.Recv(&c, 1) == 1 )
	{
		x01response.Push(c);
		x02response.Push(c);
		x03response.Push(c);
		x04response.Push(c);
		x05response.Push(c);
		x06response.Push(c);
		x0fresponse.Push(c);
		x10response.Push(c);
	}
	if( x01response.CheckResponse() == 1 )
	{
		if( ctx.GetX01Request().GetSlave() != x01response.GetSlave() )
		{
			x02response.Init();
			return 0;
		}
		//x01response.Show();
		return 0x01;
	}
	if( x02response.CheckResponse() == 1 )
	{
		if( ctx.GetX02Request().GetSlave() != x02response.GetSlave() )
		{
			x02response.Init();
			return 0;
		}
		//x02response.Show();
		return 0x02;
	}
	if( x03response.CheckResponse() == 1 )
	{
		if( ctx.GetX03Request().GetSlave() != x03response.GetSlave() )
		{
			x03response.Init();
			return 0;
		}
		//x03response.Show();
		return 0x03;
	}
	if( x04response.CheckResponse() == 1 )
	{
		if( ctx.GetX04Request().GetSlave() != x04response.GetSlave() )
		{
			x04response.Init();
			return 0;
		}
		//x04response.Show();
		return 0x04;
	}
	if( x05response.CheckResponse() == 1 )
	{
		if( ctx.GetX05Request().GetSlave() != x05response.GetSlave() )
		{
			x05response.Init();
			return 0;
		}
		x05response.Show();
		return 0x05;
	}
	if( x06response.CheckResponse() == 1 )
	{
		if( ctx.GetX06Request().GetSlave() != x06response.GetSlave() )
		{
			x06response.Init();
			return 0;
		}
		x06response.Show();
		return 0x06;
	}
	if( x0fresponse.CheckResponse() == 1 )
	{
		if( ctx.GetX0fRequest().GetSlave() != x0fresponse.GetSlave() )
		{
			x0fresponse.Init();
			return 0;
		}
		x0fresponse.Show();
		return 0x0f;
	}
	if( x10response.CheckResponse() == 1 )
	{
		if( ctx.GetX10Request().GetSlave() != x10response.GetSlave() )
		{
			x10response.Init();
			return 0;
		}
		x10response.Show();
		return 0x10;
	}
	return 0;
}
bool Modbus::RecvRequest(Mcontext& context)
{
	unsigned char c = 0;

	if( com.Recv(&c, 1) == 1 )
	{
		context.Push(c);
	}
	if( context.CheckRequest() == 1 )
	{
		return true;
	}
	return false;
}
bool Modbus::RecvResponse(Mcontext& context)
{
	unsigned char c = 0;

	if( com.Recv(&c, 1) == 1 )
	{
		context.Push(c);
	}
	if( context.CheckResponse() == 1 )
	{
		return true;
	}
	return false;
}
bool Modbus::SendRequest(Mcontext& context)
{
	ctx = context;
	context.Show();
	InitResponse();
	t.init();
	return (com.Send(ctx.GetData(), ctx.GetLength()) == ctx.GetLength());
}
bool Modbus::SendResponse(Mcontext& context)
{
	ctx = context;
	return (com.Send(ctx.GetData(), ctx.GetLength()) == ctx.GetLength());
}
Mcontext& Modbus::GetContext(void)
{
	return ctx;
}

#ifdef TEST_MODBUS
int main(int argc, char **argv)
{
	Modbus modbus;
	string comdev = "/dev/ttySX0";

	if( modbus.Init(comdev, 9600, 0, 8, 1) == false )
	{
		printf("modbus.Init failed!\n");
		return -1;
	}

	uint16_t offset = 0;
	X03Response x03res;
	TimeOperator timer;

	while(1)
	{
		if( timer.sdiff() != 0 )
		{
			X03Request x03request(1, 3, offset, 1);
			modbus.SendRequest(x03request);
			timer.init();
			printf("\nsend:");
			x03request.Show();
			++offset %= 12;
		}
		uint8_t ret = modbus.RecvResponse();
		if( 0 != ret )
		{
			printf("%d/ms recv:", timer.mdiff());
			modbus.ResponseShow(ret);
			modbus.InitResponse();
		}
		usleep(100);
	}

	return 0;
}
#endif//TEST_MODBUS
