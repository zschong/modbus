#ifndef __CGI_H__
#define __CGI_H__
#include <map>
#include "Cgicc.h"
#include "xstring.h"
using namespace cgicc;


class Cgi : public Cgicc
{
public:
	typedef map<xstring, xstring>::iterator Qiterator;
	typedef map<xstring, xstring>::iterator query_iterator;
protected:
	const xstring nullvalue;
	map<xstring, xstring> querymap;

public:
	Cgi(void)
	{
		for(form_iterator i = fFormData.begin(); i != fFormData.end(); i++)
		{
			xstring key = i->getName();
			xstring value = i->getValue();
			querymap[ key.trim() ] = value.trim();
		}
	}
public:
	query_iterator begin(void)
	{
		return querymap.begin();
	}
	query_iterator end(void)
	{
		return querymap.end();
	}
	const xstring& operator[](const xstring& key)
	{
		query_iterator value = querymap.find(key);

		if( querymap.end() == value )
		{
			return nullvalue;
		}
		return value->second;
	}
};

#endif//__CGI_H__
