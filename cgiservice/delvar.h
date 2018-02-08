#ifndef __DELVAR_H__
#define __DELVAR_H__
#include "modbusconfig.h"
#include "service.h"
#include "cgi.h"

class DelVar
{
public:
	DelVar(Cgi&, const string&, const string&);
};

#endif//__DELVAR_H__
