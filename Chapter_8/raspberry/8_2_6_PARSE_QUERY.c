#include <stdio.h>
#include <stdlib.h>
#include <parse.h>
#include "cJSON.h"
#include <string.h>
#define PARSE_URL  "http://xxx.herokuapp.com/parse"
int toggle = -1;
char tmpObjectId[11];

void mySaveCallback (ParseClient client, int error, int httpStatus, const char* httpResponseBody) 
{
  if (error == 0 && httpResponseBody != NULL) {
    cJSON* root = cJSON_Parse(httpResponseBody);
    cJSON* array = cJSON_CreateArray();
    array = cJSON_GetObjectItem(root,"results");
    if(cJSON_GetArraySize(array) > 0)
    {
      cJSON* item = cJSON_GetArrayItem(array,0);
      cJSON* object = cJSON_GetObjectItem(item,"objectId");
      if(object != NULL)
      {
        printf("objectID = %s\n", object->valuestring);
        if(tmpObjectId [0] == '\0') 
		{   
          printf("FIRST TIME : set object id\n");
          strncpy(tmpObjectId,object->valuestring,10);
        }
        else if(strncmp(tmpObjectId, object->valuestring,10) == 0) 
        {
          printf("NO CHANGE : skip process\n");
        }
        else
        {
          printf("CHANGE : new data is comming \n");
          strncpy(tmpObjectId,object->valuestring,10);
         }
       }
    }
  }
}
int main(int argc, char *argv[]) 
{
  ParseClient client = parseInitializeWithServerURL("myAppId", "myAppId", PARSE_URL);
  tmpObjectId [0] = '\0';
  while(1)
  { 
    parseSendRequest(client, "GET", "/classes/TestPi?limit=1&order=-updatedAt", NULL, mySaveCallback);
    sleep(3);
  }
  return 0;
}
