#include <stdio.h>
#include "cgi.h"

int main(void)
{
	Cgi cgi;

	printf("Content-Type:text/html\r\n");
	printf("\r\n");
	printf("\r\n");

	for(Cgi::Iterator i = cgi.begin(); i != cgi.end(); i++)
	{
		printf("[%s]=%s<p>", i->first.data(), i->second.data());
	}

	return 0;
}
