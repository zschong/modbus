#ifndef __REGISTER_OPERATOR_H__
#define __REGISTER_OPERATOR_H__
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

class RegisterOperator
{
protected:
	unsigned key;
	unsigned value;
	typedef map<unsigned,unsigned>::iterator Iterator;

public:
	RegisterOperator(void);
	RegisterOperator(int, int);
	RegisterOperator(int, int, int, int);
	RegisterOperator(int, int, int, int, int);
	RegisterOperator(int, int, int, int, int, int);
public:
	void SetKey(int);
	void SetValue(int);
public:
	int GetKey(void);
	int GetValue(void);
public:
	void SetSlave(unsigned char);
	void SetFcode(unsigned char);
	void SetOffset(unsigned short);
	void SetCount(unsigned short);
	void SetInterval(unsigned short);
	void SetComId(unsigned char);
public:
	unsigned char GetSlave(void);
	unsigned char GetFcode(void);
	unsigned short GetOffset(void);
	unsigned short GetCount(void);
	unsigned short GetInterval(void);
	unsigned char  GetComId(void);
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
#endif//__REGISTER_OPERATOR_H__
