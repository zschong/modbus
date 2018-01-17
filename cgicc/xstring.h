#ifndef __XSTRING_H__
#define __XSTRING_H__
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
using namespace std;

class xstring : public std::string
{
public:
	xstring(void){}
	xstring(const string& s){ (*this) = s; }
	xstring(const char* s){ if(s)format("%s",s); }
public:
	xstring& format(const char* fmt,...)
	{
		int r = 0;
		va_list ap;
		char buf[4096] = {0};

		va_start(ap, fmt);
		r = vsnprintf(buf, sizeof(buf), fmt, ap);
		va_end(ap);
		buf[sizeof(buf)-1] = 0;
		*this = buf;

		return (*this);
	}
	xstring& operator=(const string& s)
	{
		(*(string*)this) = s;
		return (*this);
	}
	xstring& operator=(const char* s)
	{
		if( s )
		{
			*(string*)this = s;
		}
		else
		{
			*(string*)this = "";
		}
		return (*this);
	}
	unsigned char xdigit(int i)
	{
		if( i < length() )
		{
			switch( (*(this))[i] )
			{
			case '0':
				return 0x00;
			case '1':
				return 0x01;
			case '2':
				return 0x02;
			case '3':
				return 0x03;
			case '4':
				return 0x04;
			case '5':
				return 0x05;
			case '6':
				return 0x06;
			case '7':
				return 0x07;
			case '8':
				return 0x08;
			case '9':
				return 0x09;
			case 'a':
			case 'A':
				return 0x0A;
			case 'b':
			case 'B':
				return 0x0B;
			case 'c':
			case 'C':
				return 0x0C;
			case 'd':
			case 'D':
				return 0x0D;
			case 'e':
			case 'E':
				return 0x0E;
			case 'f':
			case 'F':
				return 0x0F;
			}
		}//siwtch
		return 0;
	}//xdigit
	
	const unsigned char tochar(void)const
	{
		return 0xff & toint();
	}
	const unsigned char toshort(void) const
	{
		return 0xffff &toint();
	}
	const int toint(void)const
	{
		if( empty() )
		{
			return 0;
		}
		return atoi(data());
	}
	const int xtoint(void) const
	{
		int len = length();

		if( len < 1 )
		{
			return 0;
		}
		if( len < 3 )
		{
			return strtol(data(), 0, 16);
		}
		if( data()[2] == 'x' )
		{
			return strtol(data()+2, 0, 16);
		}
	}
	xstring operator+(const xstring& s)
	{
		xstring tmp = s;
		tmp += *this;
		return tmp;
	}
	const xstring& trim(void)
	{
		const int l = length();
		const char *s = data();
		char *e = (char*)(s + l - 1);
	
		if( l < 1 )
		{
			return (*this);
		}
		for(int i = 0; i < l; i++)
		{
			switch(*s)
			{
				case ' ':
				case '\t':
					s++;
					continue;
			}
			break;
		}
		for(int i = 0; i < l; i++, e--)
		{
			switch(*e)
			{
				case ' ':
				case '\t':
				case '\0':
					*e = 0;
					continue;
			}
			break;
		}
		return format("%s", s);
	}
};

#endif//__XSTRING_H__
