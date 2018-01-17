#include <iostream>
#include "Cgicc.h"
using namespace std;
using namespace cgicc;

int main(void)
{
	Cgicc cgi;
	const vector<FormEntry>& entry = cgi.getElements();
	const CgiEnvironment& environment = cgi.getEnvironment();
	const vector<FormFile>& files = cgi.getFiles();

	cout << "Content-Type:text/html\r\n"  << endl;
	cout << "fServerPort:" << environment.getServerPort() << "<br>" << endl;
	cout << "fServerPort:" << environment.getServerPort() << "<br>" << endl;
	cout << "fContentLength:" << environment.getContentLength() << "<br>" << endl;
	cout << "fServerSoftware:" << environment.getServerSoftware() << "<br>" << endl;
	cout << "fServerName:" << environment.getServerName() << "<br>" << endl;
	cout << "fGatewayInterface:" << environment.getGatewayInterface() << "<br>" << endl;
	cout << "fServerPorotocl:" << environment.getServerProtocol() << "<br>" << endl;
	cout << "fRequestMethod:" << environment.getRequestMethod() << "<br>" << endl;
	cout << "fPathInfo:" << environment.getPathInfo() << "<br>" << endl;
	cout << "fPathTranslated:" << environment.getPathTranslated() << "<br>" << endl;
	cout << "fScriptName:" << environment.getScriptName() << "<br>" << endl;
	cout << "fQueryString:" << environment.getQueryString() << "<br>" << endl;
	cout << "fRemoteHost:" << environment.getRemoteHost() << "<br>" << endl;
	cout << "fRemoteAddr:" << environment.getRemoteAddr() << "<br>" << endl;
	cout << "fAuthType:" << environment.getAuthType() << "<br>" << endl;
	cout << "fRemoteUser:" << environment.getRemoteUser() << "<br>" << endl;
	cout << "fRemoteIdent:" << environment.getRemoteIdent() << "<br>" << endl;
	cout << "fContentType:" << environment.getContentType() << "<br>" << endl;
	cout << "fAccept:" << environment.getAccept() << "<br>" << endl;
	cout << "fUserAgent:" << environment.getUserAgent() << "<br>" << endl;
	cout << "fPostData:" << environment.getPostData() << "<br>" << endl;
	cout << "fRedirectRequest:" << environment.getRedirectRequest() << "<br>" << endl;
	cout << "fRedirectURL:" << environment.getRedirectURL() << "<br>" << endl;
	cout << "fRedirectStatus:" << environment.getRedirectStatus() << "<br>" << endl;
	cout << "fReferrer:" << environment.getReferrer() << "<br>" << endl;
	cout << "fCookie:" << environment.getCookies() << "<br>" << endl;


	for(vector<FormEntry>::const_iterator i = entry.begin(); i != entry.end(); i++)
	{
		cout << i->getName() << "=" << i->getValue() << "<br>" << endl;	
	}
	cout << "files.size=" << files.size() << "<br>" << endl;
	for(vector<FormFile>::const_iterator i = files.begin(); i != files.end(); i++)
	{
		cout << "File name: " << i->getFilename();
		cout << "File name: " << i->getDataLength();
		cout << endl;
	}

	return 0;
}
