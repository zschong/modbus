#ifndef __GET_CONFIG_H__
#define __GET_CONFIG_H__
#include "modbusconfig.h"
#include "service.h"
#include "cgi.h"

class GetConfig
{
public:
	GetConfig(Cgi&, const string&, const string&);
};

#endif//__GET_CONFIG_H__
