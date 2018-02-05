#include <stdio.h>
#include <strings.h>
#include "comcfgfile.h"


void ComcfgFile::SetName(const string& fname)
{
	filename = fname;
}
bool ComcfgFile::Load(map<unsigned,ComConfig>& m)
{
	if( filename.empty() )
	{
		return false;
	}

	FILE *fp = fopen(filename.data(), "r");

	if( fp )
	{
		char buf[128];

		m.clear();
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
			ComConfig& comcfig = m[comid];

			comcfig.SetComId(comid);
			comcfig.SetBaudRate(baud);
			comcfig.SetParity(parity);
			comcfig.SetByteSize(bsize);
			comcfig.SetStopBit(stop);
		}
		fclose(fp);
	}
	return false;
}
bool ComcfgFile::Store(map<unsigned,ComConfig>& m)
{
	if( filename.empty() )
	{
		return false;
	}

	FILE *fp = fopen(filename.data(), "w");

	if( NULL == fp )
	{
		return false;
	}
	for(Iterator i = m.begin(); i != m.end(); i++)
	{
		char buf[128];

		int len = snprintf(buf, sizeof(buf),
								"%u,%u,%u,%u,%u\n",
								i->second.GetComId(),
								i->second.GetBaudRate(),
								i->second.GetParity(),
								i->second.GetByteSize(),
								i->second.GetStopBit()
								);
		fwrite(buf, len, 1, fp);
	}
	fclose(fp);
	return true;
}
