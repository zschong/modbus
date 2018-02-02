#ifndef __COM_CONFIG_OPERATOR_H__
#define __COM_CONFIG_OPERATOR_H__
#include <map>
#include <string>
using namespace std;

class ComConfigOperator
{
protected:
	string comname;
	unsigned baud;
	unsigned pbsc; 
public:
	ComConfigOperator(void);
	ComConfigOperator(const string&, unsigned, unsigned);
public:
	const string& GetComName(void)const;
	const unsigned GetPBSC(void)const;
public:
	void SetComName(const string&);
	void GetPBSC(const unsigned);
public:
	void SetBaud(unsigned);
	void SetParity(unsigned);
	void SetBsize(unsigned);
	void SetStop(unsigned);
	void SetComId(unsigned);
public:
	const unsigned GetBaud(void)const;
	const unsigned GetParity(void)const;
	const unsigned GetBsize(void)const;
	const unsigned GetStop(void)const;
	const unsigned GetComId(void)const;
};

#endif//__COM_CONFIG_OPERATOR_H__
