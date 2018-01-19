#ifndef __COUNT_H__
#define __COUNT_H__

class Count
{
protected:
	int value;
public:
	Count(void);
	Count(int);
public:
	int GetValue(void);
	void SetValue(int);
public:
	unsigned short GetCount(void);
	unsigned char GetInterval(void);
public:
	void SetCount(int);
	void SetInterval(int);
};

#endif//__COUNT_H__
