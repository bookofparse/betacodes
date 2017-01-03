#include <stdio.h>
#include <parse.h>
#define PARSE_URL  "http://xxx.herokuapp.com/parse"
void mySaveCallback(ParseClient client, int error, int httpStatus, const char* httpResponseBody) {
  if (error == 0 && httpResponseBody != NULL) {
    printf("%s \n",httpResponseBody);
   }
}

int main (void)
{
  ParseClient client = parseInitializeWithServerURL("myAppId", "myAppId", PARSE_URL);
  parseSendRequest(client, "POST", "/classes/TestPi", "{\"name\":\"room_2\",\"bright\":50}", NULL);
  parseSendRequest(client, "GET", "/classes/TestPi", NULL,  mySaveCallback);
  return 0;
}
