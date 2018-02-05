#include <stdio.h>
#include <strings.h>
#include "varoperator.h"
#include "varcfgfile.h"


void VarcfgFile::SetName(const string& fname)
{
	filename = fname;
}
bool VarcfgFile::Load(map<unsigned,map<unsigned,unsigned> >& m)
{
	if( filename.empty() )
	{
		return false;
	}

	FILE *fp = fopen(filename.data(), "r");

	if( fp )
	{
		char buf[256];

		m.clear();
		buf[ sizeof(buf) - 1 ] = 0;
		while( fgets(buf, sizeof(buf)-1, fp) )
		{
			unsigned comid = 0;
			unsigned slave = 0;
			unsigned fcode = 0;
			unsigned offset = 0;
			unsigned count = 0;
			unsigned interval = 0;
			VarOperator var;
			

			sscanf(buf, 
				  "%u,%u,%u,%u,%u,%u", 
				   &comid,
				   &slave,
				   &fcode,
				   &offset,
				   &count,
				   &interval);

			var.SetSlave(slave);
			var.SetFcode(fcode);
			var.SetOffset(offset);
			var.SetCount(count);
			var.SetInterval(interval);
			var.SetComId(comid);

			m[comid][var.GetKey()] = var.GetValue();
		}
		fclose(fp);
	}
	return false;
}
bool VarcfgFile::Store(map<unsigned,map<unsigned,unsigned> >& m)
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
			char buf[256];
			VarOperator var(B->first, B->second);

			int len = snprintf(buf, sizeof(buf),
									"%u,%u,%u,%u,%u,%s\n",
									var.GetComId(),
									var.GetSlave(),
									var.GetFcode(),
									var.GetOffset(),
									var.GetCount(),
									var.GetInterval()
									);
			fwrite(buf, len, 1, fp);
		}
	}
	fclose(fp);
	return true;
}
