#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "comoperator.h"

ComOperator::ComOperator(void):comfd(-1)
{
}
bool ComOperator::Close(void)
{
	uart_close(comfd);
	comfd = -1;
	return true;
}
bool ComOperator::Block(bool b)
{
	if( b )
	{
		return (fcntl(comfd, F_SETFL, fcntl(comfd, F_GETFL) & ~O_NONBLOCK) == 0);
	}
	return (fcntl(comfd, F_SETFL, fcntl(comfd, F_GETFL) | O_NONBLOCK) == 0);
}
bool ComOperator::Open(const string& path)
{
	if( -1 == comfd )
	{
		comfd = uart_open(path.data());
	}
	return (-1 != comfd);
}
bool ComOperator::Config(int baud, char parity, int bsize, int stop)
{
	switch(parity)
	{
	case 0:
	case 'n':
	case 'N':
		parity = 'N';
		break;
	case 1:
	case 'o':
	case 'O':
		parity = 'O';
		break;
	case 2:
	case 'e':
	case 'E':
		parity = 'E';
		break;
	}
	return (uart_config(comfd, baud, parity, bsize, stop) == 0);
}
int ComOperator::Recv(unsigned char *buf, int len)
{
	return uart_read(comfd, (char*)buf, len);
}
int  ComOperator::Send(unsigned char *data, int len)
{
	return uart_write(comfd, (const char*)data, len);
}

#ifdef TEST_COMPORT
int main(int argc, char **argv)
{
	ComOperator com;
	char *p = (char*)"/dev/ttySX0";

	if( argc > 1 )
	{
		p = argv[1];
	}
	if( com.Open(p) == false )
	{
		printf("com.open(%s) failed!\n", p);
		return -1;
	}
	if( com.Config(9600, 0, 8, 1) == false )
	{
		printf("com.Config() failed!\n");
		return -2;
	}
	if( com.Block(false) == false )
	{
		printf("com.Block() failed!\n");
		return -3;
	}
	while(1)
	{
		unsigned char c = 0;

		if( com.Recv(&c, 1) == 1 )
		{
			printf("%02X ", c);
		}
		usleep(1000);
	}

	return 0;
}
#endif//TEST_COMPORT
