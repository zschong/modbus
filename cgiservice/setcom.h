#ifndef __SETCOM_H__
#define __SETCOM_H__
#include "modbusconfig.h"
#include "service.h"
#include "cgi.h"

class SetCom
{
public:
	SetCom(Cgi&, const string&, const string&);
};

#endif//__SETCOM_H__
