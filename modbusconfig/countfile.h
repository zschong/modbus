#ifndef __COUNT_FILE_H__
#define __COUNT_FILE_H__
#include <map>
#include <string>
class SendRecv;
using namespace std;

class SendRecvCount
{
public:
	unsigned char slave;
	unsigned char fcode;
	unsigned short offset;
	unsigned short count;
	unsigned short send;
	unsigned short recv;
public:
	SendRecvCount(void):slave(0),fcode(0),offset(0),count(0),send(0),recv(0){}
};
class CountFile
{
protected:
	string filename;
public:
	void SetFileName(const string&);
public:
	bool Store(map<unsigned,map<unsigned,SendRecvCount> >&);
public:
	typedef map<unsigned,map<unsigned,SendRecvCount> >::iterator AIterator;
	typedef map<unsigned,SendRecvCount>::iterator BIterator;
};


#endif//__COUNT_FILE_H__
