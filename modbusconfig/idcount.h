#ifndef __ID_COUNT_H__
#define __ID_COUNT_H__
#include <map>
using namespace std;

class IdCount
{
public:
	void Add(map<int,int> &m, int id, int count);
	void Del(map<int,int> &m, int id, int count);
};
#endif//__ID_COUNT_H__
