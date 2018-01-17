#include "timeoperator.h"

TimeOperator::TimeOperator(void)
{
	init();
}
int TimeOperator::init(void)
{
	return gettimeofday(&t, 0);
}
const int TimeOperator::sdiff(void)const
{
	struct timeval n;

	if( gettimeofday(&n, 0) )
	{
		return 0;
	}
	return n.tv_sec - t.tv_sec;
}
const int TimeOperator::mdiff(void)const
{
	struct timeval n;

	if( gettimeofday(&n, 0) )
	{
		return 0;
	}
	return (n.tv_sec - t.tv_sec) * 1000 + (n.tv_usec - t.tv_usec) / 1000;
}
const int TimeOperator::udiff(void) const
{
	struct timeval n;

	if( gettimeofday(&n, 0) )
	{
		return 0;
	}
	return (n.tv_sec - t.tv_sec) * 1000 * 1000 + (n.tv_usec - t.tv_usec);
}
