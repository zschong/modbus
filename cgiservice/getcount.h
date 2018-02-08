#ifndef __GET_COUNT_H__
#define __GET_COUNT_H__
#include "modbusconfig.h"
#include "countfile.h"
#include "service.h"
#include "cgi.h"

class GetCount
{
public:
	GetCount(Cgi&, const string&, const string&);
};

#endif//__GET_COUNT_H__
