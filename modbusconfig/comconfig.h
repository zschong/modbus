#ifndef __COM_CONFIG_H__
#define __COM_CONFIG_H__
#include <string>
#include <string.h>
using namespace std;

class ComConfig
{
	typedef enum
	{
		IndexComId     = 0,
		IndexBaudRate0 = 1,
		IndexBaudRate1 = 2,
		IndexBaudRate2 = 3,
		IndexBaudRate3 = 4,
		IndexParity    = 5,
		IndexByteSize  = 6,
		IndexStopBit   = 7,
	}IndexTypeDefine;
protected:
	unsigned char buffer[8];
public:
	ComConfig(void);
	ComConfig(int comid, int baud, int parity, int bsize, int stop);
public:
	const int GetComId(void)const;
	const int GetBaudRate(void)const;
	const int GetParity(void)const;
	const int GetByteSize(void)const;
	const int GetStopBit(void)const;
public:
	void SetComId(const int comid);
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
