#ifndef __GETVAR_H__
#define __GETVAR_H__
#include "cgi.h"

class GetVar
{
public:
	GetVar(void);
	GetVar(Cgi& cgi);
public:
	bool Service(Cgi& cgi);
};

#endif//__GETVAR_H__
