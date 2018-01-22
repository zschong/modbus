#ifndef __ID_COUNT_H__
#define __ID_COUNT_H__
#include <map>
#include <string>
using namespace std;

typedef enum
{
	RangeCDAB = 1,
	RangeCADB = 2,
	RangeCABD = 3,
	RangeACDB = 4,
	RangeACBD = 5,
	RangeABCD = 6,
}RangeType;

class IdCount
{
protected:
	int key;
	int value;

public:
	IdCount(void);
	IdCount(int, int);
	IdCount(int, int, int, int, int);
public:
	int GetKey(void);
	int GetValue(void);
	void SetKey(int);
	void SetValue(int);
public:
	void SetSlave(unsigned char);
	void SetFcode(unsigned char);
	void SetOffset(unsigned short);
	void SetCount(unsigned short);
	void SetInterval(unsigned char);
public:
	unsigned char GetSlave(void);
	unsigned char GetFcode(void);
	unsigned short GetOffset(void);
	unsigned short GetCount(void);
	unsigned char GetInterval(void);
public:
	void Add(map<int,int> &m, int id, int count);
	void Del(map<int,int> &m, int id, int count);
public:
	int CalcRange(int A, int B, int C, int D);
	string RangeToString(int range);
	
};
#endif//__ID_COUNT_H__
