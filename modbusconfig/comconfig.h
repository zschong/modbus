#ifndef __COM_CONFIG_H__
#define __COM_CONFIG_H__
#include <string>
#include <string.h>
using namespace std;

class ComConfig
{
	typedef enum
	{
		IndexComNameA  = 0,
		IndexComNameZ  = 120,
		IndexBaudRate0 = 121,
		IndexBaudRate1 = 122,
		IndexBaudRate2 = 123,
		IndexBaudRate3 = 124,
		IndexParity    = 125,
		IndexByteSize  = 126,
		IndexStopBit   = 127 
	}IndexTypeDefine;
protected:
	unsigned char buffer[128];
public:
	ComConfig(void);
	ComConfig(const string& com, int baud, int parity, int bsize, int stop);
public:
	const string GetComName(void)const;
	const int GetBaudRate(void)const;
	const int GetParity(void)const;
	const int GetByteSize(void)const;
	const int GetStopBit(void)const;
public:
	void SetComName(const string& comname);
	void SetBaudRate(const int baud);
	void SetParity(const int parity);
	void SetByteSize(const int bsize);
	void SetStopBit(const int stop);
public:
	ComConfig& operator=(const ComConfig& com);
public:
	void Show(void);
};

#endif//__COM_CONFIG_H__
