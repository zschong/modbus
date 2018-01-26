#ifndef __SETVAR_H__
#define __SETVAR_H__
#include "cgi.h"

class SetVar
{
public:
	SetVar(void);
	SetVar(Cgi& cgi);
public:
	bool Service(Cgi& cgi);
};

#endif//__SETVAR_H__
