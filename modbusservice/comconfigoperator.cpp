#include "comconfigoperator.h"


ComConfigOperator::ComConfigOperator(void):baud(0),pbsc(0)
{
}
ComConfigOperator::ComConfigOperator(const string& c, unsigned b, unsigned p)
:comname(c),baud(b),pbsc(p)
{
}
const string& ComConfigOperator::GetComName(void)const
{
	return comname;
}
const unsigned ComConfigOperator::GetPBSC(void)const
{
	return pbsc;
}
void ComConfigOperator::SetComName(const string& com)
{
	comname = com;
}
void ComConfigOperator::GetPBSC(const unsigned p)
{
	pbsc = p;
}
void ComConfigOperator::SetBaud(unsigned b)
{
	baud = b;
}
void ComConfigOperator::SetParity(unsigned parity)
{
	pbsc &= ~(0xff << 24);
	pbsc |= (0xff << 24) & (parity << 24);
}
void ComConfigOperator::SetBsize(unsigned bsize)
{
	pbsc &= ~(0xff << 16);
	pbsc |= (0xff << 16) & (bsize << 16);
}
void ComConfigOperator::SetStop(unsigned stop)
{
	pbsc &= ~(0xff << 8);
	pbsc |= (0xff << 8) & (stop << 8);
}
void ComConfigOperator::SetComId(unsigned comid)
{
	pbsc &= ~(0xff << 0);
	pbsc |= (0xff << 0) & (comid << 0);
}
const unsigned ComConfigOperator::GetBaud(void)const
{
	return baud;
}
const unsigned ComConfigOperator::GetParity(void)const
{
	return 0xff & (pbsc >> 24);
}
const unsigned ComConfigOperator::GetBsize(void)const
{
	return 0xff & (pbsc >> 16);
}
const unsigned ComConfigOperator::GetStop(void)const
{
	return 0xff & (pbsc >> 8);
}
const unsigned ComConfigOperator::GetComId(void)const
{
	return 0xff & (pbsc >> 0);
}
