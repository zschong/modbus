#include <stdio.h>
#include "varid.h"


VarId::VarId(void)
{
	value = 0;
}
VarId::VarId(int v)
{
	value = v;
}
void VarId::SetValue(int v)
{
	value = v;
}
int  VarId::GetValue(void)
{
	return value;
}
unsigned char VarId::GetSlave(void)
{
	return (unsigned char)(value >> 24);
}
unsigned char VarId::GetFcode(void)
{
	return (unsigned char)(value >> 16);
}
unsigned short VarId::GetOffset(void)
{
	return (unsigned short)value;
}
void VarId::SetSlave(int slave)
{
	value &= ~(0xff << 24);
	value |= ((slave << 24) & (0xff << 24));
}
void VarId::SetFcode(int fcode)
{
	value &= ~(0xff << 16);
	value |= ((fcode << 16) & (0xff << 16));
}
void VarId::SetOffset(int offset)
{
	value &= ~(0xffff);
	value |= ((offset) & (0xffff));
}

#ifdef TEST_VARID
int main(void)
{
	VarId varid;

	varid.SetSlave(0x01);
	varid.SetFcode(0x03);
	varid.SetOffset(0x000C);

	printf("varid.GetSlave(%02X)\n", varid.GetSlave());
	printf("varid.GetFcode(%02X)\n", varid.GetFcode());
	printf("varid.GetOffset(%04X)\n", varid.GetOffset());
	printf("varid.GetValue(%08X)\n", varid.GetValue());

	return 0;
}
#endif//TEST_VARID
