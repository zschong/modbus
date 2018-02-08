#ifndef __ADDVAR_H__
#define __ADDVAR_H__
#include "modbusconfig.h"
#include "service.h"
#include "cgi.h"

class AddVar 
{
public:
	AddVar(Cgi&, const string&, const string&);
};

#endif//__ADDVAR_H__
