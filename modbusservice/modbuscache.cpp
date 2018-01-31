#include <stdio.h>
#include "modbuscache.h"

bool ModbusCache::GetValue(map<unsigned, map<unsigned,ModbusValue> >& vmap)
{
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
void ModbusCache::DelValue(unsigned comid, unsigned varid)
{
	valuemap[ comid ].erase( varid );
}
void ModbusCache::ShowValue(void)
{
	ShowValue(valuemap);
}
void ModbusCache::ShowValue(map<unsigned,map<unsigned,ModbusValue> >& vmap)
{
	for(CVIterator A = vmap.begin(); A != vmap.end(); A++)
	{
		for(VIterator B = A->second.begin(); B != A->second.end(); B++)
		{
			printf("ModbusCache::%s(comid=%d, %08X)\n", 
					__func__, A->first, B->first);
		}
	}
}
