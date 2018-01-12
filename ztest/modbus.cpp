#include <time.h>
#include "modbus.h"
#include "timeoperator.h"

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
			printf("%d(ms) recv:", timer.mdiff());
			modbus.ResponseShow(ret);
			modbus.InitResponse();
		}
		usleep(100);
	}

	return 0;
}
