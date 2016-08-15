#include <stdio.h>
#include <stdlib.h>
#include <parse.h>
#include "cJSON.h"
#include <string.h>
#include <time.h>
#include <wiringPi.h>  //wiringPi.h ¼±¾ð
#include <softPwm.h>

#define PARSE_URL  http://whispering-tundra-13887.herokuapp.com/parse
#define ON 1
#define OFF 0
#define OUTPIN 7
#define SERVO_ON 5
#define SERVO_OFF 25

int toggle = -1;
char tmpObjectId[11];
char usrId[10];
char data[100];
char data_objId[100];
int sw_state = OFF;

int GetCurtSec(void)
{
  time_t timer;
  struct tm *t;
  timer = time(NULL); 
  t = localtime(&timer); 
  return t->tm_sec;
}

void setSw(int inData)
{
  if(inData == 1) 
  {
    softPwmWrite(OUTPIN, SERVO_ON) ;
  }
  else
  {
    softPwmWrite(OUTPIN, SERVO_OFF) ;
  }
}

void mySaveCallback (ParseClient client, int error, int httpStatus, const char* httpResponseBody) 
{
  if (error == 0 && httpResponseBody != NULL) 
  {
    cJSON* root = cJSON_Parse(httpResponseBody);
    cJSON* array = cJSON_CreateArray();
    array = cJSON_GetObjectItem(root,"results");
    if(cJSON_GetArraySize(array) > 0)
    {
      cJSON* item = cJSON_GetArrayItem(array,0);
      cJSON* objectId = cJSON_GetObjectItem(item,"objectId");
      cJSON* objectRqst = cJSON_GetObjectItem(item,"sw_rqst");
      cJSON* objectState = cJSON_GetObjectItem(item,"state");
            
      if(objectId != NULL) 
      {
				
        if(objectRqst->valueint == ON) 
	    {
	      if(objectState->valueint == sw_state)
	      {
		     printf("No CHANGE : state:%d, rqst:%d \n",sw_state, objectState->valueint);
		  }
          else
          {
		    printf("CHANGE : state:%d, rqst:%d \n",sw_state, objectState->valueint);
		    sw_state = objectState->valueint;
		    setSw(sw_state);
	      }
          sprintf(data,"{\"usrId\":\"%s\",\"locate\":\"room_1\",\"state\":%d,\"sw_rqst\":0}",usrId,sw_state);
          sprintf(data_objId,"/classes/iot_switch/%s",objectId->valuestring);
          parseSendRequest(client, "PUT",data_objId, data, NULL);
       }
       else
       {
         printf("NO RQST \n");
       }
	}
    else
    {
      sprintf(data,"{\"usrId\":\"%s\",\"locate\":\"room_1\",\"state\":%d,\"sw_rqst\":0}",usrId,sw_state);
      printf("POST \n",data);
      parseSendRequest(client, "POST","/classes/iot_switch", data, NULL);
    } 
  }  
}

int main(int argc, char *argv[]) 
{
  int flagWr = 1;
  int tmpSec = 0; 
  int bufSec = 0;
  if (wiringPiSetup() == -1) 
    exit(1) ;  //init wiringPi
  pinMode(OUTPIN, OUTPUT) ;  //set the 0 pin as OUTPUT
  digitalWrite(OUTPIN, LOW) ;  //0 pin output LOW voltage
  softPwmCreate(OUTPIN, 0, 200) ;  //pwm initialize HIGH time 0, LOW time 200ms 
  printf("please enter your id : ");
  scanf("%s",usrId);
  ParseClient client = parseInitializeWithServerURL("myAppId", "myAppId",PARSE_URL);
  tmpObjectId [0] = '\0';
  while(1)
  { 
    tmpSec = GetCurtSec();
    if(tmpSec != bufSec)
    {
      printf("%d\n",tmpSec);
      flagWr = 1;
    }
    bufSec = tmpSec;
    if((tmpSec%10 == 0)  && (flagWr))
    {
      flagWr = 0;
      printf("check server \n");
      sprintf(data,"/classes/iot_switch?limit=1&order=-updatedAt&where={\"usrId\":\"%s\"}",usrId);
      //printf("%s \n",data);
      parseSendRequest(client, "GET", data, NULL, mySaveCallback);
    }
  }
  return 0;
}
