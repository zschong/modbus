#include <stdio.h>
#include "valuefile.h"
#include "varoperator.h"

void ValueFile::SetFileName(const string& fname)
{
	filename = fname;
}
bool ValueFile::Store(map<unsigned,map<unsigned,ModbusValue> >& m)
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
			char buf[128];
			VarOperator x(B->first, 0);

			len = snprintf(buf, sizeof(buf), 
							"%u,%u,%u,%u,%u,%u,%u\n",
							A->first,
							x.GetKey(),
							x.GetSlave(),
							x.GetFcode(),
							x.GetOffset(),
							B->second.GetValue(),
							B->second.mdiff()
							);
			fwrite(buf, len, 1, fp);
		}
	}
	fclose(fp);
	return true;
}
