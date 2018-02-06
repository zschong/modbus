#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "comcfgfile.h"


bool ComcfgFile::Load(const string& fname)
{
	if( fname.empty() )
	{
		return false;
	}
	filename = fname;

	FILE *fp = fopen(filename.data(), "r");

	if( fp )
	{
		char buf[128];

		buf[ sizeof(buf) - 1 ] = 0;
		while( fgets(buf, sizeof(buf)-1, fp) )
		{
			unsigned comid = 0;
			unsigned baud = 0;
			unsigned parity = 0;
			unsigned bsize = 0;
			unsigned stop = 0;

			sscanf(buf, 
				  "%u,%u,%u,%u,%u", 
				   &comid,
				   &baud,
				   &parity,
				   &bsize,
				   &stop
				  );
			ComConfig& com = comcfgmap[comid];

			com.SetComId(comid);
			com.SetBaudRate(baud);
			com.SetParity(parity);
			com.SetByteSize(bsize);
			com.SetStopBit(stop);
		}
		fclose(fp);
	}
	return true;
}
bool ComcfgFile::Store(void)
{
	if( filename.empty() )
	{
		return false;
	}
	printf("ComcfgFile::Store(%s)\n", filename.data());

	FILE *fp = fopen(filename.data(), "w");

	if( NULL == fp )
	{
		return false;
	}
	for(Iterator i = comcfgmap.begin(); i != comcfgmap.end(); i++)
	{
		char buf[128];

		snprintf(buf, sizeof(buf),
				"%u,%u,%u,%u,%u\n",
				i->second.GetComId(),
				i->second.GetBaudRate(),
				i->second.GetParity(),
				i->second.GetByteSize(),
				i->second.GetStopBit()
				);
		buf[ sizeof(buf) - 1 ] = 0;
		fwrite(buf, strlen(buf), 1, fp);
	}
	fclose(fp);
	return true;
}
void ComcfgFile::SetComConfig(const ComConfig& com)
{
	comcfgmap[ com.GetComId() ] = com;
}
ComcfgFile::Iterator ComcfgFile::begin(void)
{
	return comcfgmap.begin();
}
ComcfgFile::Iterator ComcfgFile::end(void)
{
	return comcfgmap.end();
}
