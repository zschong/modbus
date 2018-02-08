#ifndef __SET_NAME_H__
#define __SET_NAME_H__
#include "modbusconfig.h"
#include "service.h"
#include "cgi.h"

class SetName
{
public:
	SetName(Cgi&, const string&, const string&);
};

#endif//__SET_NAME_H__
