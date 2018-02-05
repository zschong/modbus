#include <stdio.h>
#include <strings.h>
#include "comidname.h"

bool ComIdName::LoadComId(const string& fname)
{
	if( fname.empty() )
	{
		return false;
	}
	
	FILE *fp = fopen(fname.data(), "r");

	if( NULL == fp )
	{
		return false;
	}

	char buf[256];

	bzero(buf, sizeof(buf));
	while( fgets(buf, sizeof(buf)-1, fp) )
	{
		unsigned comid = 0;
		char comname[255] = {0};

		bzero(comname, sizeof(comname));
		sscanf(buf, "%u,%s", &comid, comname);
		SetComId(comname, comid);
		bzero(buf, sizeof(buf));
	}
	fclose(fp);
	return true;
}
void ComIdName::SetComId(const string& name, unsigned id)
{
	nameid[ name ] = id;
	idname[ id   ] = name;
	printf("comname(%s).comid(%d)\n", name.data(), id);
}
unsigned ComIdName::GetComId(const string& name)
{
	map<string,unsigned>::iterator i = nameid.find(name);

	if( nameid.end() == i )
	{
		return 0;
	}
	return i->second;
}
const string& ComIdName::GetComName(unsigned id)
{
	map<unsigned,string>::iterator i = idname.find(id);

	if( idname.end() == i )
	{
		return nullname;
	}
	return i->second;
}
