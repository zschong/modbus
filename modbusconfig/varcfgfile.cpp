#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "varoperator.h"
#include "varcfgfile.h"


bool VarcfgFile::Load(const string& fname)
{
	if( fname.empty() )
	{
		return false;
	}
	filename = fname;

	FILE *fp = fopen(fname.data(), "r");

	if( fp )
	{
		char buf[256];

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

			varcfgmap[comid][var.GetKey()] = var.GetValue();
		}
		fclose(fp);
	}
	return false;
}
bool VarcfgFile::Store(void)
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
	for(AIterator A = varcfgmap.begin(); A != varcfgmap.end(); A++)
	{
		for(BIterator B = A->second.begin(); B != A->second.end(); B++)
		{
			char buf[256];
			VarOperator var(B->first, B->second);

			snprintf(buf, sizeof(buf),
					"%u,%u,%u,%u,%u,%u\n",
					var.GetComId(),
					var.GetSlave(),
					var.GetFcode(),
					var.GetOffset(),
					var.GetCount(),
					var.GetInterval()
					);
			buf[ sizeof(buf) - 1 ] = 0;
			fwrite(buf, strlen(buf), 1, fp);
		}
	}
	fclose(fp);
	return true;
}
void VarcfgFile::SetVarConfig(unsigned comid, map<unsigned,unsigned> &m)
{
	varcfgmap.erase( comid );
	varcfgmap[ comid ] = m;
}
VarcfgFile::AIterator VarcfgFile::begin(void)
{
	return varcfgmap.begin();
}
VarcfgFile::AIterator VarcfgFile::end(void)
{
	return varcfgmap.end();
}
