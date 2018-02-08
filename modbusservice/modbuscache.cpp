#include <stdio.h>
#include "modbuscache.h"

void ModbusCache::DelByTime(void)
{
	map<unsigned,map<unsigned,TimeOperator> >::iterator A;
	map<unsigned,TimeOperator>::iterator B;
	map<unsigned,map<unsigned,unsigned> > m;

	for(A = delmap.begin(); A != delmap.end(); A++)
	{
		for(B = A->second.begin(); B != A->second.end(); B++)
		{
			if( B->second.mdiff() < 500 )
			{
				continue;
			}
			if( B->second.mdiff() > 1000 )
			{
				valuemap[ A->first ].erase( B->first );
			}
			if( B->second.mdiff() > 3000 )
			{
				m[A->first][ B->first ];
			}
		}
	}

	map<unsigned,map<unsigned,unsigned> >::iterator X;
	map<unsigned,unsigned>::iterator Y;

	for(X = m.begin(); X != m.end(); X++)
	{
		for(Y = X->second.begin(); Y != X->second.end(); Y++)
		{
			delmap[ X->first ].erase( Y->first );
		}
	}
}
bool ModbusCache::GetValue(map<unsigned, map<unsigned,ModbusValue> >& vmap)
{
	DelByTime();
	vmap.clear();
	vmap = valuemap;
	return vmap.begin() != vmap.end();
}
void ModbusCache::SetVarName(unsigned comid, unsigned varid, const string& name)
{
	valuemap[ comid ][ varid ].SetVarName( name );
}
void ModbusCache::SetValue(unsigned comid, unsigned varid, unsigned value)
{
	ModbusValue& v = valuemap[ comid ][ varid ];

	v.SetComId( comid );
	v.SetVarId( varid );
	v.SetValue( value );
}
void ModbusCache::DelValue(unsigned comid, unsigned varid, unsigned count)
{
	for(int i = 0; i < count; i++)
	{
		valuemap[ comid ].erase( varid + i );
		delmap[ comid ][ (varid + i) ].init();
	}
}
void ModbusCache::ShowValue(void)
{
	ShowValue(valuemap);
}
void ModbusCache::ShowValue(map<unsigned,map<unsigned,ModbusValue> >& vmap)
{
	for(AIterator A = vmap.begin(); A != vmap.end(); A++)
	{
		for(BIterator B = A->second.begin(); B != A->second.end(); B++)
		{
			printf("ModbusCache::%s(comid=%d, %08X)\n", 
					__func__, A->first, B->first);
		}
	}
}
