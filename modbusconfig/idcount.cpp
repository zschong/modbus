#include "varid.h"
#include "count.h"
#include "idcount.h"


void IdCount::Add(map<int,int>& m, int id, int count)
{
	for(map<int,int>::iterator i = m.begin(); i != m.end(); i++)
	{
		VarId sv(id);
		Count sc(count);
		VarId dv(i->first);
		Count dc(i->second);

		if( sv.GetSlave() != dv.GetSlave() )
		{
			continue;
		}
		if( sv.GetFcode() != dv.GetFcode() )
		{
			continue;
		}
		int sofs = sv.GetOffset();
		int scnt = sc.GetCount();
		int dofs = dv.GetOffset();
		int dcnt = dc.GetCount();
	}
}
void IdCount::Del(map<int,int>& m, int id, int count)
{
	for(map<int,int>::iterator i = m.begin(); i != m.end(); i++)
	{
	}
}
