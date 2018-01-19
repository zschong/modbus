#include <stdio.h>
#include "count.h"


Count::Count(void)
{
	value = 0;
}
Count::Count(int v)
{
	value = v;
}
int Count::GetValue(void)
{
	return value;
}
void Count::SetValue(int v)
{
	value = v;
}
unsigned short Count::GetCount(void)
{
	return (unsigned short)(value >> 16);
}
unsigned char Count::GetInterval(void)
{
	return (unsigned char)(value >> 8);
}
void Count::SetCount(int count)
{
	value &= ~(0xffff << 16);
	value |= (count << 16);
}
void Count::SetInterval(int interval)
{
	value &= ~(0xff << 8);
	value |= ((0xff << 8) & (interval << 8));
}

#ifdef TEST_COUNT
int main(void)
{
	Count count;

	count.SetCount(0x11);
	count.SetInterval(100);

	printf("count.GetCount(%04X)\n", count.GetCount());
	printf("count.GetInterval(%02X)\n", count.GetInterval());
	printf("count.GetValue(%08X)\n", count.GetValue());

	return 0;
}
#endif//TEST_COUNT
