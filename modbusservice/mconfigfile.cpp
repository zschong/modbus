#include <stdio.h>
#include "mconfigfile.h"

MconfigFile::MconfigFile(void)
{
}
MconfigFile::MconfigFile(const string& fname):filename(fname)
{
}
void MconfigFile::SetFileName(const string& fname)
{
	filename = fname;
}
bool MconfigFile::WriteConfig(map<unsigned,map<unsigned,unsigned> >& mmu)
{
	if( filename.empty() )
	{
		return false;
	}

	string data;
	FILE *fp = fopen(filename.data(), "w");

	if( NULL == fp )
	{
		return false;
	}
	for(IIterator A = mmu.begin(); A != mmu.end(); A++)
	{
		for(Iterator B = A->second.begin(); B != A->second.end(); B++)
		{
			char buf[32];
			snprintf(buf, sizeof(buf), 
					"%08X:%08X:%08X\n", 
					A->first, B->first, B->second);
			data += buf;
		}
	}
	int len = data.length();
	if( fwrite(data.data(), len, 1, fp) != 1 )
	{
		fclose(fp);
		return false;
	}
	fclose(fp);
	return true;
}
bool MconfigFile::ReadConfig(map<unsigned,map<unsigned,unsigned> >& mmu)
{
	if( filename.empty() )
	{
		return false;
	}

	FILE *fp = fopen(filename.data(), "r");

	if( NULL == fp )
	{
		return false;
	}
	mmu.clear();
	while(fp)
	{
		char buf[32] = {0};
		unsigned A = 0;
		unsigned B = 0;
		unsigned C = 0;
		if( fgets(buf, sizeof(buf), fp) )
		{
			sscanf(buf, "%08X:%08X:%08X", &A, &B, &C);
			mmu[A][B] = C;
		}
	}
	fclose(fp);

	return true;
}
void MconfigFile::Show(map<unsigned,map<unsigned,unsigned> >& mmu)
{
	for(IIterator A = mmu.begin(); A != mmu.end(); A++)
	{
		for(Iterator B = A->second.begin(); B != A->second.end(); B++)
		{
			printf("%08X:%08X:%08X\n", A->first, B->first, B->second);
		}
	}
}
