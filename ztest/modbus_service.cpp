#include <stdio.h>
#include <unistd.h>
#include "modbusmanager.h"


void ShowValue(map<int,int>& values)
{
	for(map<int,int>::iterator i = values.begin(); i != values.end(); i++)
	{
		printf("\tvalue(%08X, %08X)=%d\n", i->first, i->second, i->second >> 16);
	}
}
int main(void)
{
	ModbusManager manager;
	map<string,map<int,int> > values;
	map<string,map<int,int> >::iterator it;

	manager.SetComConfig( ComConfig("/dev/ttySX0", 9600, 0, 8, 1) );
	manager.SetVarConfig( VarConfig("/dev/ttySX0", VarCmdAdd, 1, 3, 0, 1, 80) );
	manager.SetVarConfig( VarConfig("/dev/ttySX0", VarCmdAdd, 1, 3, 1, 2, 80) );
	manager.SetVarConfig( VarConfig("/dev/ttySX0", VarCmdAdd, 1, 3, 2, 3, 80) );
	manager.SetVarConfig( VarConfig("/dev/ttySX0", VarCmdAdd, 1, 3, 3, 4, 80) );
                                                                              
	while(1)
	{
		if( manager.GetValue(values) )
		{
			for(it = values.begin(); it != values.end(); it++)
			{
				printf("values from(%s):\n", it->first.data());
				ShowValue(it->second);
			}
		}
		usleep(100);
	}

	return 0;
}
