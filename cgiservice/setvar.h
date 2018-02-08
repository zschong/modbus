#ifndef __SETVAR_H__
#define __SETVAR_H__
#include "modbusconfig.h"
#include "service.h"
#include "cgi.h"

class SetVar
{
public:
	SetVar(Cgi&, const string&, const string&);
};

#endif//__SETVAR_H__
