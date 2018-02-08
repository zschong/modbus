#include <stdio.h>
#include "getcount.h"

GetCount::GetCount(Cgi& cgi, const string& serverpath, const string& clientpath)
{
	Service service;
	ModbusConfig mconfig;

	int comid = cgi["comid"].toint();
	int slave = cgi["slave"].toint();
	int fcode = cgi["fcode"].toint();
	map<unsigned,map<unsigned,SendRecvCount> > m;
	map<unsigned,map<unsigned,SendRecvCount> >::iterator A;
	map<unsigned,SendRecvCount>::iterator B;

	char buf[128];
	FILE *fp = fopen("var/count", "r");

	if( NULL == fp )
	{
		printf("{\"success\":false}");
		return;
	}
	while( fgets(buf, sizeof(buf)-1, fp) )
	{
		unsigned comid = 0;
		unsigned slave = 0;
		unsigned fcode = 0;
		unsigned offset= 0;
		unsigned count = 0;
		unsigned send = 0;
		unsigned recv = 0;
		sscanf(buf, "%u,%u,%u,%u,%u,%u,%u",
				&comid,
				&slave,
				&fcode,
				&offset,
				&count,
				&send,
				&recv
			  );
		VarOperator x(slave, fcode, offset, count);
		SendRecvCount &c = m[comid][x.GetKey()];
		c.slave = slave;
		c.fcode = fcode;
		c.offset= offset;
		c.count = count;
		c.send  = send;
		c.recv  = recv;
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
					"\"slave\":\"%u\""
					","
					"\"fcode\":\"%u\""
					","
					"\"offset\":\"%u\""
					","
					"\"count\":\"%u\""
					","
					"\"sendcount\":\"%u\""
					","
					"\"recvcount\":\"%u\""
					"},",
					A->first,
					B->second.slave,
					B->second.fcode,
					B->second.offset,
					B->second.count,
					B->second.send,
					B->second.recv
					);
		}
	}
	printf("{}]}");
}
