#include <stdio.h>
#include "idcount.h"


IdCount::IdCount(void):key(0),value(0)
{
}
IdCount::IdCount(int i, int c):key(i),value(c)
{
}
IdCount::IdCount(int slave, int fcode, int offset, int count, int interval):key(0),value(0)
{
	SetSlave(slave);
	SetFcode(fcode);
	SetOffset(offset);
	SetCount(count);
	SetInterval(interval);
}
void IdCount::SetKey(int i)
{
	key = i;
}
void IdCount::SetValue(int v)
{
	value = v;
}
void IdCount::SetSlave(unsigned char slave)
{
	key = (key & ~(0xff << 24));
	key = (key | (slave << 24));
}
void IdCount::SetFcode(unsigned char fcode)
{
	key = (key & ~(0xff << 16));
	key = (key | (fcode << 16));
}
void IdCount::SetOffset(unsigned short offset)
{
	key = (key & ~(0xffff <<  0));
	key = (key | (offset <<  0));
}
void IdCount::SetCount(unsigned short count)
{
	value =(value & ~(0xffff << 16));
	value =(value | (count << 16));
}
void IdCount::SetInterval(unsigned char interval)
{
	value =(value & ~(0xff << 8));
	value =(value | (interval << 8));
}
unsigned char IdCount::GetSlave(void)
{
	return 0xff & (key >> 24);
}
unsigned char IdCount::GetFcode(void)
{
	return 0xff & (key >> 16);
}
unsigned short IdCount::GetOffset(void)
{
	return 0xffff & (key >> 0);
}
unsigned short IdCount::GetCount(void)
{
	return 0xffff & (value >> 16);
}
unsigned char IdCount::GetInterval(void)
{
	return 0xff & (value >>  8);
}
int IdCount::GetKey(void)
{
	return key;
}
int IdCount::GetValue(void)
{
	return value;
}

void IdCount::Add(map<int,int>& m, int key, int value)
{
	for(map<int,int>::iterator i = m.begin(); i != m.end(); i++)
	{
		IdCount n(key, value);
		IdCount o(i->first, i->second);

		if( n.GetSlave() != o.GetSlave() )
		{
			continue;
		}
		if( n.GetFcode() != o.GetFcode() )
		{
			continue;
		}
		int A = o.GetOffset();
		int B = A + o.GetCount();
		int C = n.GetOffset();
		int D = C + n.GetCount();
		switch( CalcRange(A, B, C, D) )
		{
			case RangeCADB:
				m.erase(o.GetKey());
				n.SetCount(B - C);
				m[n.GetKey()] = o.GetValue();
				return;
			case RangeCABD:
				m.erase(o.GetKey());
				m[n.GetKey()] = n.GetValue();
				return;
			case RangeACDB:
				return;
			case RangeACBD:
				o.SetCount(D - A);
				m[o.GetKey()] = o.GetValue();
				return;
		}
	}
	m[key] = value;
}
void IdCount::Del(map<int,int>& m, int key, int value)
{
	for(map<int,int>::iterator i = m.begin(); i != m.end(); i++)
	{
		IdCount n(key, value);
		IdCount o(i->first, i->second);

		if( n.GetSlave() != o.GetSlave() )
		{
			continue;
		}
		if( n.GetFcode() != o.GetFcode() )
		{
			continue;
		}
		int A = o.GetOffset();
		int B = A + o.GetCount();
		int C = n.GetOffset();
		int D = C + n.GetCount();
		printf("%s,%d:A(%d), B(%d), C(%d), D(%d)\n", __func__, __LINE__, A, B, C, D);
		switch( CalcRange(A, B, C, D) )
		{
			case RangeCADB:
				m.erase(o.GetKey());
				o.SetOffset(D);
				o.SetCount(B - D);
				m[o.GetKey()] = o.GetValue();
				return;
			case RangeCABD:
				m.erase(o.GetKey());
				return;
			case RangeACDB:
				m.erase(o.GetKey());
				o.SetCount(C - A);
				printf("%s,%d:o.GetOffset(%d), o.GetCount(%d)\n", __func__, __LINE__, o.GetOffset(), o.GetCount());
				n.SetOffset(D);
				n.SetCount(B - D);
				m[o.GetKey()] = o.GetValue();
				m[n.GetKey()] = n.GetValue();
				return;
			case RangeACBD:
				m.erase(o.GetKey());
				o.SetCount(C - A);
				m[o.GetKey()] = o.GetValue();
				return;
		}
	}
	m[key] = value;
}
int IdCount::CalcRange(int A, int B, int C, int D)
{
	if( (C <= D) && (D <= A) && (A <= B) )
	{
		return RangeCDAB;
	}

	if( (C <= A) && (A <= D) && (D <= B) )
	{
		return RangeCADB;
	}

	if( (C <= A) && (A <= B) && (B <= D) )
	{
		return RangeCABD;
	}

	if( (A <= C) && (C <= D) && (D <= B) )
	{
		return RangeACDB;
	}

	if( (A <= C) && (C <= B) && (B <= D) )
	{
		return RangeACBD;
	}

	if( (A <= B) && (B <= C) && (C <= D) )
	{
		return RangeABCD;
	}
	return 0;
}
string IdCount::RangeToString(int range)
{
	switch(range)
	{
		case RangeCDAB:
			return "CDAB";
		case RangeCADB:
			return "CADB";
		case RangeCABD:
			return "CABD";
		case RangeACDB:
			return "ACDB";
		case RangeACBD:
			return "ACBD";
		case RangeABCD:
			return "ABCD";
	}
	return "UNKONW";
}
#ifdef TEST_IDCOUNT
int mainA(void)
{
	IdCount c;
	int A = 1;
	int B = 1;
	int C = 1;
	int D = 1;

	//CDAB
	C = 1, D = 5, A = 6, B = 9;
	printf("%s\n", c.RangeToString(c.CalcRange(A, B, C, D)).data());

	//CADB
	C = 1, A = 5, D = 6, B = 9;
	printf("%s\n", c.RangeToString(c.CalcRange(A, B, C, D)).data());

	//CABD
	C = 1, A = 5, B = 6, D = 9;
	printf("%s\n", c.RangeToString(c.CalcRange(A, B, C, D)).data());

	//ACDB
	A = 1, C = 5, D = 6, B = 9;
	printf("%s\n", c.RangeToString(c.CalcRange(A, B, C, D)).data());

	//ACBD
	A = 1, C = 5, B = 6, D = 9;
	printf("%s\n", c.RangeToString(c.CalcRange(A, B, C, D)).data());

	//ABCD
	A = 1, B = 5, C = 6, D = 9;
	printf("%s\n", c.RangeToString(c.CalcRange(A, B, C, D)).data());

	return 0;
}
int main(void)
{
	map<int,int> m;
	IdCount a(1, 3, 0, 7, 100);
	IdCount b(1, 3, 3, 6, 100);
	IdCount c(1, 3, 5, 9, 100);

	c.Add(m, a.GetKey(), a.GetValue());
	c.Add(m, b.GetKey(), b.GetValue());
	c.Add(m, c.GetKey(), c.GetValue());

	c.Del(m, b.GetKey(), b.GetValue());
	c.Add(m, b.GetKey(), b.GetValue());
	//c.Del(m, a.GetKey(), a.GetValue());
	c.Del(m, c.GetKey(), c.GetValue());


	for(map<int,int>::iterator i = m.begin(); i != m.end(); i++)
	{
		printf("<%08X, %08X>\n", i->first, i->second);
	}

	return 0;
}
#endif//TEST_IDCOUNT
