#include <stdio.h>
#include "idcount.h"
#include "valuefile.h"


ValueFile::ValueFile(void)
{
}
ValueFile::ValueFile(map<string, map<int,Value> > &mmv)
{
	MakeFile(mmv);
}
void ValueFile::SetComMap(const string& combase, const string& alias)
{
	if( combase.empty() )
	{
		return;
	}
	if( alias.empty() )
	{
		return;
	}
	sscom.clear();
	for(int i = 0; i < 32; i++)
	{
		char key[128];
		char value[128];
		snprintf(key, sizeof(key), "%s%d", combase.data(), i);
		snprintf(value, sizeof(value), "%s%d", alias.data(), i);
		sscom[key] = value;
	}
}
void ValueFile::MakeFile(map<string, map<int,Value> > &mmv)
{
	map<string,list<Value> > mslv;
	map<string,map<int,Value> >::iterator A;

	for(A = mmv.begin(); A != mmv.end(); A++)
	{
		map<int,Value>::iterator B;
		string com = sscom[A->first];
		char comname[128];

		snprintf(comname, sizeof(comname), "var/%s.json", com.data());

		for(B = A->second.begin(); B != A->second.end(); B++)
		{
			IdCount x(B->first, 0);
			int slave = x.GetSlave();
			char buf[128] = {0};
			snprintf(buf, sizeof(buf), "var/%s.%d.json", com.data(), slave);
			B->second.SetCom(com);
			B->second.SetId(B->first);
			mslv[string(buf)].push_back(B->second);
		}
		MakeComFile(comname, A->second);
	}
	map<string,list<Value> >::iterator C;
	for(C = mslv.begin(); C != mslv.end(); C++)
	{
		MakeSlaveFile(C->first, C->second);
	}
	MakeAllComFile("var/allcom.json", mslv);
}
void ValueFile::MakeSlaveFile(const string& f, list<Value> &vlist)
{
	FILE *fp = NULL; 

	if( f.empty() || vlist.empty() )
	{
		return;
	}
	if( (fp = fopen(f.data(), "w"))  == NULL )
	{
		return;
	}
	fwrite("[", 1, 1, fp);
	for(list<Value>::iterator i = vlist.begin(); i != vlist.end(); i++)
	{
		char buf[256];
		snprintf(buf, sizeof(buf), 
				"{\"name\":\"%s\","
				"\"com\":\"%s\","
				"\"id\":\"%08X\","
				"\"value\":\"%d\","
				"\"cost\":\"%d\"},",
				i->GetName().data(),
				i->GetCom().data(), 
				i->GetId(), 
				i->GetValue(),
				i->mdiff());
		fwrite(buf, string(buf).length(), 1, fp);
	}
	fwrite("{}]", 3, 1, fp);
	fclose(fp);
}
void ValueFile::MakeComFile(const string& f, map<int,Value> &vmap)
{
	FILE *fp = NULL; 

	if( f.empty() || vmap.empty() )
	{
		return;
	}
	if( (fp = fopen(f.data(), "w"))  == NULL )
	{
		return;
	}
	fwrite("[", 1, 1, fp);
	for(map<int,Value>::iterator i = vmap.begin(); i != vmap.end(); i++)
	{
		char buf[256];
		int len = snprintf(buf, sizeof(buf), 
							"{\"name\":\"%s\","
							"\"com\":\"%s\","
							"\"id\":\"%08X\","
							"\"value\":\"%d\","
							"\"cost\":\"%d\"},",
							i->second.GetName().data(),
							i->second.GetCom().data(), 
							i->second.GetId(), 
							i->second.GetValue(),
							i->second.mdiff());
		fwrite(buf, len, 1, fp);
	}
	fwrite("{}]", 3, 1, fp);
	fclose(fp);
}
void ValueFile::MakeAllComFile(const string& f, map<string,list<Value> > &mslv)
{
	FILE *fp = NULL; 

	if( f.empty() || mslv.empty() )
	{
		return;
	}
	if( (fp = fopen(f.data(), "w"))  == NULL )
	{
		return;
	}
	fwrite("[", 1, 1, fp);
	map<string,list<Value> >::iterator A;
	for(A = mslv.begin(); A != mslv.end(); A++)
	{
		list<Value>::iterator B;
		for(B = A->second.begin(); B != A->second.end(); B++)
		{
			char buf[256];
			snprintf(buf, sizeof(buf), 
					"{\"name\":\"%s\","
					"\"com\":\"%s\","
					"\"id\":\"%08X\","
					"\"value\":\"%d\","
					"\"cost\":\"%d\"},",
					B->GetName().data(),
					B->GetCom().data(), 
					B->GetId(), 
					B->GetValue(),
					B->mdiff());
			fwrite(buf, string(buf).length(), 1, fp);
		}
	}
	fwrite("{}]", 3, 1, fp);
	fclose(fp);
}
