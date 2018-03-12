#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>
#include <map>
#include <string>
#include <exception>
using namespace std;

string kv(const string& k, const string& v)
{
	return string("\"") + k + string("\":\"") + v + string("\"");
}

bool PostJson(map<string,string>& m, const string& url)
{
	string json = "{";

	for(map<string,string>::iterator i = m.begin(); i != m.end(); i++)
	{
		json += kv(i->first, i->second) + ",";
	}
	json[ (json.length()-1) ] = '}';
	printf("json(%s)\n", json.data());

    try
    {
        CURL *pCurl = NULL;
        CURLcode res;

        // In windows, this will init the winsock stuff
        curl_global_init(CURL_GLOBAL_ALL);

        // get a curl handle
        pCurl = curl_easy_init();
        if (NULL != pCurl)
        {
            // 设置超时时间为1秒
            curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 1);

            // First set the URL that is about to receive our POST.
            // This URL can just as well be a
            // https:// URL if that is what should receive the data.
            curl_easy_setopt(pCurl, CURLOPT_URL, url.data());

            // 设置http发送的内容类型为JSON
            curl_slist *plist = curl_slist_append(NULL,
                "Content-Type:application/json;charset=UTF-8");
            curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, plist);

            // 设置要POST的JSON数据
            curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, json.data());

            // Perform the request, res will get the return code
            res = curl_easy_perform(pCurl);
            // Check for errors
            if (res != CURLE_OK)
            {
                printf("curl_easy_perform() failed:%s\n", curl_easy_strerror(res));
            }
            // always cleanup
            curl_easy_cleanup(pCurl);
        }
        curl_global_cleanup();
    }
    catch (std::exception &ex)
    {
        printf("curl exception %s.\n", ex.what());
    }

	return true;
}

int main(int argc, char *argv[])
{
	map<string,string> m;
	string url = "192.168.1.1";


	m["varnid"] = "123456";
	m["varname"] = "temperature";

	if( argc > 1 )
	{
		url = argv[1];
	}

	while(1)
	{
		char buf[32];

		snprintf(buf, sizeof(buf), "%08X", time(0));
		m["timestamp"] = buf;
		PostJson(m, url);
		sleep(1);
	}
	if( PostJson(m, url) )
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

