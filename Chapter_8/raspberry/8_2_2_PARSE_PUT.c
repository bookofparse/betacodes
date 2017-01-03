#include <stdio.h>
#include <parse.h>
#define PARSE_URL  "http://xxx.herokuapp.com/parse"
int main (void)
{
  ParseClient client = parseInitializeWithServerURL("myAppId", "myAppId", PARSE_URL);
  parseSendRequest(client, "PUT", "/classes/TestPi/xAJJk8R6Mk", "{\"bright\":10}", NULL);
  return 0;
}
