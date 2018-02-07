#include <stdio.h>
#include "countfile.h"
#include "varoperator.h"

void CountFile::SetFileName(const string& fname)
{
	filename = fname;
}
bool CountFile::Store(map<unsigned,map<unsigned,SendRecvCount> >& m)
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

	for(AIterator A = m.begin(); A != m.end(); A++)
	{
		for(BIterator B = A->second.begin(); B != A->second.end(); B++)
		{
			int len = 0;
			char buf[512];

			len = snprintf(buf, sizeof(buf), 
							"%u,%u,%u,%u,%u,%u,%u\n",
							A->first,
							B->second.slave,
							B->second.fcode,
							B->second.offset,
							B->second.count,
							B->second.send,
							B->second.recv
							);
			fwrite(buf, len, 1, fp);
		}
	}
	fclose(fp);
	return true;
}
