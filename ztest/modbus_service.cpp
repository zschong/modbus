#include <stdio.h>
#include <map>
#include "modbus.h"
#include "service.h"
#include "timeoperator.h"
#include "modbusconfig.h"


int main(void)
{
	Modbus modbus;
	ComConfig com("/dev/ttySX0", 9600, 0, 8, 1);
	VarConfig var("/dev/ttySX0", 0, 1, 5, 0, 1);

	printf("com.GetComName(%s)\n", com.GetComName().data());
	printf("com.GetBaudRate(%d)\n", com.GetBaudRate());
	printf("com.GetParity(%d)\n", com.GetParity());
	printf("com.GetByteSize(%d)\n", com.GetByteSize());
	printf("com.GetStopBit(%d)\n", com.GetStopBit());

	printf("var.GetComName(%s)\n", var.GetComName().data());
	printf("var.GetCommand(%d)\n", var.GetCommand());
	printf("var.GetSlave(%d)\n", var.GetSlave());
	printf("var.GetFcode(%d)\n", var.GetFcode());
	printf("var.GetOffset(%d)\n", var.GetOffset());
	printf("var.GetValue(%d)\n", var.GetValue());

	return 0;
}
