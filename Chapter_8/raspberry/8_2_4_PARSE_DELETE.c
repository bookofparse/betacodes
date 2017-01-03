#include <stdio.h>
#include <parse.h>
#define PARSE_URL  "http://xxx.herokuapp.com/parse"
int main (void)
{
  ParseClient client = parseInitializeWithServerURL("myAppId", "myAppId", PARSE_URL);
  parseSendRequest(client, "DELETE", "/classes/TestPi/xAJJk8R6Mk ", NULL, NULL);
  return 0;
}
