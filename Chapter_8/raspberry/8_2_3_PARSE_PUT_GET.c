#include <stdio.h>
#include <parse.h>
#define PARSE_URL  "http:// 192.168.219.106:1337/parse"
void mySaveCallback(ParseClient client, int error, int httpStatus, const char* httpResponseBody) {
  if (error == 0 && httpResponseBody != NULL) {
    printf("%s \n",httpResponseBody);
  }
}

int main (void)
{
  ParseClient client = parseInitializeWithServerURL("myAppId", "myAppId", PARSE_URL);
  parseSendRequest(client, "PUT", "/classes/TestPi/xAJJk8R6Mk ", "{\"bright\":20}", NULL);
  parseSendRequest(client, "GET", "/classes/TestPi", NULL,  mySaveCallback);
  return 0;
}
