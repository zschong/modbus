#include "varconfig.h"

VarConfig::VarConfig(void)
{
	memset(buffer, 0, sizeof(buffer));
}
VarConfig::VarConfig(const string& comname, int cmd, int slave, int fcode, int offset, int value)
{
	SetComName(comname);
	SetCommand(cmd);
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetValue(value);
}
const string VarConfig::GetComName(void)
{
	buffer[ IndexComNameZ ] = 0;
	return (char*)buffer;
}
const int VarConfig::GetCommand(void)
{
	return (int)buffer[ IndexCommand ];
}
const int VarConfig::GetSlave(void)
{
	return (int)buffer[ IndexSlave ];
}
const int VarConfig::GetFcode(void)
{
	return (int)buffer[ IndexFcode ];
}
const int VarConfig::GetOffset(void)
{
	int offset = 0;

	offset += (buffer[ IndexOffset0 ] << 8);
	offset += (buffer[ IndexOffset1 ] << 0);

	return offset;
}
const int VarConfig::GetValue(void)
{
	int value = 0;

	value += (buffer[ IndexValue0 ] << 8);
	value += (buffer[ IndexValue1 ] << 0);

	return value;
}

void VarConfig::SetComName(const string& comname)
{
	if( comname.empty() == false )
	{
		snprintf((char*)buffer, IndexComNameZ, "%s", comname.data());
	}
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
void VarConfig::SetValue(const int value)
{
	buffer[ IndexValue0 ] = 0xff & (value >> 8);
	buffer[ IndexValue1 ] = 0xff & (value >> 0);
}


