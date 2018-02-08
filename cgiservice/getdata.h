#ifndef __GET_DATA_H__
#define __GET_DATA_H__
#include "modbusconfig.h"
#include "service.h"
#include "cgi.h"

class GetData
{
public:
	GetData(Cgi&, const string&, const string&);
};

#endif//__GET_DATA_H__
