#include <stdio.h>
#include "idcount.h"
#include "valuefile.h"


ValueFile::ValueFile(void)
{
}
ValueFile::ValueFile(const string& n, map<unsigned,map<unsigned,ModbusValue> > &m)
{
	SetFileName(n);
	MakeFile(m);
}
void ValueFile::SetFileName(const string& fname)
{
	filename = fname;
}
void ValueFile::MakeFile(map<unsigned,map<unsigned,ModbusValue> > &mmv)
{
	MakeAllComFile(mmv);
	return;
	for(CVIterator A = mmv.begin(); A != mmv.end(); A++)
	{
		MakeComFile(A->first, A->second);
	}
}
void ValueFile::MakeComFile(unsigned comid, map<unsigned,ModbusValue> &vmap)
{
	FILE *fp = NULL; 
	char fname[128];
	map<unsigned,list<ModbusValue> > slavemap;
	typedef map<unsigned,list<ModbusValue> >::iterator VLIterator;

	snprintf(fname, sizeof(fname), "var/COM%d.json", comid);
	if( (fp = fopen(fname, "w"))  == NULL )
	{
		return;
	}
	fwrite("[", 1, 1, fp);
	for(VIterator i = vmap.begin(); i != vmap.end(); i++)
	{
		char buf[256];
		IdCount x(i->second.GetVarId(), i->second.GetValue());

		int len = snprintf(buf, sizeof(buf), 
							"{"
							"\"varname\":\"%s\""
							","
							"\"comid\":\"%d\""
							","
							"\"varid\":\"%08X\""
							","
							"\"value\":\"%d\""
							","
							"\"cost\":\"%d\""
							","
							"\"slave\":\"%d\""
							","
							"\"fcode\":\"%d\""
							","
							"\"offset\":\"%04d\""
							"},",
							i->second.GetVarName().data(),
							i->second.GetComId(),
							i->second.GetVarId(), 
							i->second.GetValue(),
							i->second.mdiff(),
							x.GetSlave(),
							x.GetFcode(),
							x.GetOffset()
							);
		fwrite(buf, len, 1, fp);
		slavemap[ IdCount(i->first,0).GetSlave() ].push_back( i->second );
	}
	fwrite("{}]", 3, 1, fp);
	fclose(fp);
	for(VLIterator i = slavemap.begin(); i != slavemap.end(); i++)
	{
		MakeSlaveFile(comid, i->first, i->second);
	}
}
void ValueFile::MakeSlaveFile(unsigned cid,unsigned vid, list<ModbusValue> &vlist)
{
	FILE *fp = NULL; 
	char fname[128];

	snprintf(fname, sizeof(fname), "var/COM%d.%d.json", cid, vid);

	if( (fp = fopen(fname, "w"))  == NULL )
	{
		return;
	}
	fwrite("[", 1, 1, fp);
	for(list<ModbusValue>::iterator i = vlist.begin(); i != vlist.end(); i++)
	{
		char buf[256];
		IdCount x(i->GetVarId(), i->GetValue());

		snprintf(buf, sizeof(buf), 
				"{"
				"\"varname\":\"%s\""
				","
				"\"comid\":\"%d\""
				","
				"\"varid\":\"%08X\""
				","
				"\"value\":\"%d\""
				","
				"\"cost\":\"%d\""
				","
				"\"slave\":\"%d\""
				","
				"\"fcode\":\"%d\""
				","
				"\"offset\":\"%04d\""
				"},",
				i->GetVarName().data(),
				i->GetComId(),
				i->GetVarId(), 
				i->GetValue(),
				i->mdiff(),
				x.GetSlave(),
				x.GetFcode(),
				x.GetOffset()
				);
		fwrite(buf, string(buf).length(), 1, fp);
	}
	fwrite("{}]", 3, 1, fp);
	fclose(fp);
}
void ValueFile::MakeAllComFile(map<unsigned,map<unsigned,ModbusValue> > &mmv)
{
	FILE *fp = NULL; 

	if( filename.empty() )
	{
		return;
	}
	if( (fp = fopen(filename.data(), "w"))  == NULL )
	{
		return;
	}
	fwrite("[", 1, 1, fp);
	for(CVIterator A = mmv.begin(); A != mmv.end(); A++)
	{
		for(VIterator B = A->second.begin(); B != A->second.end(); B++)
		{
			char buf[256];
			IdCount x(B->second.GetVarId(), B->second.GetValue());

			snprintf(buf, sizeof(buf), 
					"{"
					"\"varname\":\"%s\""
					","
					"\"comid\":\"%d\""
					","
					"\"varid\":\"%08X\""
					","
					"\"value\":\"%d\""
					","
					"\"cost\":\"%d\""
					","
					"\"slave\":\"%d\""
					","
					"\"fcode\":\"%d\""
					","
					"\"offset\":\"%04d\""
					"},",
					B->second.GetVarName().data(),
					B->second.GetComId(), 
					B->second.GetVarId(), 
					B->second.GetValue(),
					B->second.mdiff(),
					x.GetSlave(),
					x.GetFcode(),
					x.GetOffset()
					);
			fwrite(buf, string(buf).length(), 1, fp);
		}
	}
	fwrite("{}]", 3, 1, fp);
	fclose(fp);
}
