#include <stdio.h>
#include <parse.h>
#define PARSE_URL  "http://xxx.herokuapp.com/parse"
int main(int argc, char *argv[]) {
  ParseClient client = parseInitializeWithServerURL("myAppId", "myAppId", PARSE_URL);
  parseSendRequest(client, "POST", "/classes/TestPi", "{\"name\":\"room_5\",\"bright\":100}", NULL);
  return 0;
}
