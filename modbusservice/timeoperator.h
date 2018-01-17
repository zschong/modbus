#ifndef __TIME_OPERATOR_H__
#define __TIME_OPERATOR_H__
#include <sys/time.h>

class TimeOperator
{
protected:
	struct timeval t;
public:
	TimeOperator(void);

public:
	int init(void);
	const int sdiff(void)const;
	const int mdiff(void)const;
	const int udiff(void)const;
};

#endif//__TIME_OPERATOR_H__
