#include <stdio.h>
#include <parse.h>
#define PARSE_URL  "http:// 192.168.219.106:1337/parse"
int main (void)
{
  ParseClient client = parseInitializeWithServerURL("myAppId", "myAppId", PARSE_URL);
  parseSendRequest(client, "DELETE", "/classes/TestPi/xAJJk8R6Mk ", NULL, NULL);
  return 0;
}
