#include <stdio.h>
#include "getconfig.h"

GetConfig::GetConfig(Cgi& cgi, const string& serverpath, const string& clientpath)
{
	char buf[4096] = {0};
	FILE *fp = fopen("com.config", "r");

	if( NULL == fp )
	{
		return;
	}
	if( fread(buf, 1, sizeof(buf), fp) < 1 )
	{
		return;
	}
	buf[sizeof(buf)-1] = 0;
	printf("%s", buf);
}
