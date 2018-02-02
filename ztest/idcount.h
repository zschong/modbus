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
	unsigned key;
	unsigned value;
	typedef map<unsigned,unsigned>::iterator Iterator;

public:
	IdCount(void);
	IdCount(int, int);
	IdCount(int, int, int, int);
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
public:
	unsigned char GetSlave(void);
	unsigned char GetFcode(void);
	unsigned short GetOffset(void);
	unsigned short GetCount(void);
public:
	void Add(map<unsigned,unsigned> &m, int id, int count);
	void Del(map<unsigned,unsigned> &m, int id, int count);
protected:
	void Delx(map<unsigned,unsigned> &m, int id, int count);
	void Merge(map<unsigned,unsigned> &m, int id, int count);
	void Merge(map<unsigned,unsigned> &m);
	void Split(map<unsigned,unsigned> &m);
public:
	int GetABCD(int A, int B, int C, int D);
	string RangeToString(int range);
public:	
	void Show(map<unsigned,unsigned>&);
};
#endif//__ID_COUNT_H__
