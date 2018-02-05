#include <stdio.h>
#include "varconfig.h"

VarConfig::VarConfig(void)
{
	memset(buffer, 0, sizeof(buffer));
}
VarConfig::VarConfig(int comid, int cmd, VarOperator &roperator)
{
	SetComId(comid);
	SetCommand(cmd);
	SetSlave(roperator.GetSlave());
	SetFcode(roperator.GetFcode());
	SetOffset(roperator.GetOffset());
	SetValue(roperator.GetCount());
}
VarConfig::VarConfig(int comid, int cmd, int slave, int fcode, int offset, int value)
{
	SetComId(comid);
	SetCommand(cmd);
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetValue(value);
}
const int VarConfig::GetComId(void)const
{
	return (int)buffer[ IndexComId ];
}
const int VarConfig::GetCommand(void)const
{
	return (int)buffer[ IndexCommand ];
}
const int VarConfig::GetSlave(void)const
{
	return (int)buffer[ IndexSlave ];
}
const int VarConfig::GetFcode(void)const
{
	return (int)buffer[ IndexFcode ];
}
const int VarConfig::GetOffset(void)const
{
	int offset = 0;

	offset += (buffer[ IndexOffset0 ] << 8);
	offset += (buffer[ IndexOffset1 ] << 0);

	return offset;
}
const int VarConfig::GetCount(void)const
{
	int count = 0;

	count += (buffer[ IndexValue0 ] << 8);
	count += (buffer[ IndexValue1 ] << 0);

	return count;
}
const int VarConfig::GetValue(void)const
{
	int value = 0;

	value += (buffer[ IndexValue0 ] << 8);
	value += (buffer[ IndexValue1 ] << 0);

	return value;
}

void VarConfig::SetComId(const int comid)
{
	buffer[ IndexComId ] = 0xff & comid;
}
void VarConfig::SetCommand(const int cmd)
{
	buffer[ IndexCommand ] = 0xff & cmd;
}
void VarConfig::SetSlave(const int slave)
{
	buffer[ IndexSlave ] = 0xff & slave;
}
void VarConfig::SetFcode(const int fcode)
{
	buffer[ IndexFcode ] = 0xff & fcode;
}
void VarConfig::SetOffset(const int offset)
{
	buffer[ IndexOffset0 ] = 0xff & (offset >> 8);
	buffer[ IndexOffset1 ] = 0xff & (offset >> 0);
}
void VarConfig::SetCount(const int count)
{
	buffer[ IndexValue0 ] = 0xff & (count >> 8);
	buffer[ IndexValue1 ] = 0xff & (count >> 0);
}
void VarConfig::SetValue(const int value)
{
	buffer[ IndexValue0 ] = 0xff & (value >> 8);
	buffer[ IndexValue1 ] = 0xff & (value >> 0);
}
VarConfig& VarConfig::operator=(const VarConfig& var)
{
	memcpy(buffer, var.buffer, sizeof(var.buffer));
	return *this;
}
void VarConfig::Show(void)
{
	printf("VarConfig");
	printf(".comid(%d)", GetComId());
	printf(".cmd(%d)", GetCommand());
	printf(".slave(%d)", GetSlave());
	printf(".fcode(%d)", GetFcode());
	printf(".offset(%d)", GetOffset());
	printf(".count(%d)\n", GetCount());
}
