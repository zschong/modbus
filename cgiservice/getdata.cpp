#include <stdio.h>
#include "getdata.h"

class TmpNode 
{
public:
	unsigned slave;
	unsigned fcode;
	unsigned offset;
	unsigned value;
	unsigned update;
	TmpNode(void):slave(0),fcode(0),offset(0),value(0),update(0){}
};

GetData::GetData(Cgi& cgi, const string& serverpath, const string& clientpath)
{
	Service service;
	ModbusConfig mconfig;

	int comid = cgi["comid"].toint();
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();
	map<unsigned,map<unsigned,TmpNode> > m;
	map<unsigned,map<unsigned,TmpNode> >::iterator A;
	map<unsigned,TmpNode>::iterator B;

	char buf[128];
	FILE *fp = fopen("var/data", "r");

	if( NULL == fp )
	{
		printf("{\"success\":false}");
		return;
	}
	while( fgets(buf, sizeof(buf)-1, fp) )
	{
		unsigned varid = 0;
		unsigned comid = 0;
		unsigned slave = 0;
		unsigned fcode = 0;
		unsigned offset= 0;
		unsigned value = 0;
		unsigned update = 0;
		sscanf(buf, "%u,%u,%u,%u,%u,%u,%u",
				&comid,
				&varid,
				&slave,
				&fcode,
				&offset,
				&value,
				&update
			  );
		TmpNode &data = m[comid][varid];
		data.slave = slave;
		data.fcode = fcode;
		data.offset= offset;
		data.value = value;
		data.update= update;
	}
	fclose(fp);

	printf("{\"\":\"\",\"list\":[");
	for(A = m.begin(); A != m.end(); A++)
	{
		if( 0 != comid && A->first != comid )
		{
			continue;
		}
		for(B = A->second.begin(); B != A->second.end(); B++)
		{
			if( 0 != slave && slave != B->second.slave )
			{
				continue;
			}
			if( 0 != fcode && fcode != B->second.fcode )
			{
				continue;
			}
			printf("{"
					"\"comid\":\"%u\""
					","
					"\"varid\":\"%02X%08X\""
					","
					"\"slave\":\"%u\""
					","
					"\"fcode\":\"%u\""
					","
					"\"offset\":\"%05u\""
					","
					"\"value\":\"%u\""
					","
					"\"update\":\"%u\""
					"},",
					A->first,
					A->first,
					B->first,
					B->second.slave,
					B->second.fcode,
					B->second.offset,
					B->second.value,
					B->second.update
					);
		}
	}
	printf("{}]}");

	return;
}
