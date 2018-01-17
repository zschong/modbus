#include "CgiApi.h"
using namespace cgicc;

int main(int argc, char **argv)
{
	CgiApi cgi;

	printf("Content-Type:text/html\n\n");

	for(CgiApi::query_iterator i = cgi.begin(); i != cgi.end(); i++)
	{
		printf("<br>[%s] = %s\n", i->first.data(), i->second.data());
	}

	return 0;
}
