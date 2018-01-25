#ifndef __ID_COUNT_H__
#define __ID_COUNT_H__
#include <map>
#include <string>
using namespace std;

typedef enum
{
	CountX03 = 125,
	CountX01 = 2000,
}CountType;
typedef enum
{
	ABCD,//A <= B <= C <= D
	ACBD,//A <= C <= B <= D
	ACDB,//A <= C <= D <= B
	CDAB,//C <= D <= A <= B
	CADB,//C <= A <= D <= B
	CABD,//C <= A <= B <= D
}ABCDType;                   

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
protected:
	void Delx(map<int,int> &m, int id, int count);
	void Merge(map<int,int> &m, int id, int count);
	void Merge(map<int,int> &m);
	void Split(map<int,int> &m);
public:
	int GetABCD(int A, int B, int C, int D);
	string RangeToString(int range);
	
};
#endif//__ID_COUNT_H__
