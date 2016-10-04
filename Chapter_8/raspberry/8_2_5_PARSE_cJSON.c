#include <stdio.h>
#include <stdlib.h>
#include <parse.h>
#include "cJSON.h"
#define PARSE_URL  "http://xxx.herokuapp.com/parse"
void mySaveCallback (ParseClient client, int error, int httpStatus, const char* httpResponseBody)
{
  int cnt = 0;
  if (error == 0 && httpResponseBody != NULL)
  {
    printf("str = %s\n\r", httpResponseBody);
    cJSON* root = cJSON_Parse(httpResponseBody);
    cJSON* array = cJSON_CreateArray();
    array = cJSON_GetObjectItem(root,"results");
    printf("array size: %d\n\r",cJSON_GetArraySize(array));
    for(cnt=0; cJSON_GetArraySize(array) > cnt ; cnt++ )
    {
      cJSON* item = cJSON_GetArrayItem(array,cnt);
      cJSON* object = cJSON_GetObjectItem(item,"objectId");
      if(object != NULL) 
        printf("objectID = %s\n", object->valuestring);
    }
  }
}

int main(int argc, char *argv[]) 
{
	
  ParseClient client = parseInitializeWithServerURL("myAppId", "myAppId", PARSE_URL);
  while(1)
  { 
    parseSendRequest(client, "GET", "/classes/TestPi", NULL, mySaveCallback);
    sleep(3);
  }
  return 0;
}
