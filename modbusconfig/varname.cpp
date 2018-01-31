#include <stdio.h>
#include "varname.h"

VarName::VarName(void)
{
	memset(buffer, 0, sizeof(buffer));
}
VarName::VarName(int comid, int slave, int fcode, int offset, const string& vname)
{
	SetComId(comid);
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetVarName(vname);
}
const string VarName::GetVarName(void)const
{
	return (char*)(&buffer[IndexVarNameA]);
}
const int VarName::GetComId(void)const
{
	return (int)buffer[ IndexComId ];
}
const int VarName::GetSlave(void)const
{
	return (int)buffer[ IndexSlave ];
}
const int VarName::GetFcode(void)const
{
	return (int)buffer[ IndexFcode ];
}
const int VarName::GetOffset(void)const
{
	int offset = 0;

	offset += (buffer[ IndexOffset0 ] << 8);
	offset += (buffer[ IndexOffset1 ] << 0);

	return offset;
}

void VarName::SetVarName(const string& varname)
{
	if( varname.empty() == false )
	{
		snprintf((char*)(&buffer[IndexVarNameA]), 128, "%s", varname.data());
	}
}
void VarName::SetComId(const int comid)
{
	buffer[ IndexComId ] = 0xff & comid;
}
void VarName::SetSlave(const int slave)
{
	buffer[ IndexSlave ] = 0xff & slave;
}
void VarName::SetFcode(const int fcode)
{
	buffer[ IndexFcode ] = 0xff & fcode;
}
void VarName::SetOffset(const int offset)
{
	buffer[ IndexOffset0 ] = 0xff & (offset >> 8);
	buffer[ IndexOffset1 ] = 0xff & (offset >> 0);
}
VarName& VarName::operator=(const VarName& var)
{
	memcpy(buffer, var.buffer, sizeof(var.buffer));
	return *this;
}
void VarName::Show(void)
{
	printf("VarName");
	printf(".com(%d)", GetComId());
	printf(".slave(%d)", GetSlave());
	printf(".fcode(%d)", GetFcode());
	printf(".offset(%d)", GetOffset());
	printf(".name(%s)\n", GetVarName().data());
}
