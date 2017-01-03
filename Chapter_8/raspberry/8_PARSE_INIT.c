#include <stdio.h>
#include <parse.h>
#define PARSE_URL  "http://xxx.herokuapp.com/parse"
int main(int argc, char *argv[]) {
  ParseClient client = parseInitializeWithServerURL("myAppId", "myAppId",PARSE_URL);
  parseSendRequest(client, "POST", "/classes/TestObject", "{\"foo\":\"bar\"}", NULL);
  return 0;
}
