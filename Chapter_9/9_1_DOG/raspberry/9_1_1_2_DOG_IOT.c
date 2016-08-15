#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <parse.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define PARSE_URL  "http://whispering-tundra-13887.herokuapp.com/parse"
#define MPU6050_ID	0x68
#define MPU6050_ACC_X_H 0x3B
#define MPU6050_ACC_X_L 0x3C
#define MPU6050_ACC_Y_H 0x3D
#define MPU6050_ACC_Y_L 0x3E
#define MPU6050_ACC_Z_H 0x3F
#define MPU6050_ACC_Z_L 0x40
#define SEC30            (30)
#define ALPHA (0.9)
#define ACC_SCALE (16384.0)

int GetCurtSec(void)
{
  time_t timer;
  struct tm *t;
  timer = time(NULL); 
  t = localtime(&timer); 
  return t->tm_sec;
}

int main(void)
{
  int flagWr = 1;
  char data[100];
  int fd;
  short acc_x,acc_y,acc_z=0;
  float fAcc_x,fAcc_y,fAcc_z=0;
  int tmpSec = 0; 
  int bufSec = 0;
  float activity = 0;

  ParseClient client = parseInitializeWithServerURL("myAppId", "myAppId", PARSE_URL);

  printf("IOT DOG \n");
	
  wiringPiSetup();  
  if((fd=wiringPiI2CSetup(MPU6050_ID))<0)
  {
    printf("can't find i2c!!\n");        
    return fd;
  }
  wiringPiI2CWriteReg8(fd,0x6B,00);
	
  memset(data,0,sizeof(data));

  while(1)
  {
    acc_x = wiringPiI2CReadReg8(fd,MPU6050_ACC_X_H)<<8; 
    acc_x |= wiringPiI2CReadReg8(fd,MPU6050_ACC_X_L);
    acc_y = wiringPiI2CReadReg8(fd,MPU6050_ACC_Y_H)<<8;
    acc_y |= wiringPiI2CReadReg8(fd,MPU6050_ACC_Y_L);
    acc_z = wiringPiI2CReadReg8(fd,MPU6050_ACC_Z_H)<<8;
    acc_z |= wiringPiI2CReadReg8(fd,MPU6050_ACC_Z_L);
    fAcc_x = (float)acc_x/ACC_SCALE;
    fAcc_y = (float)acc_y/ACC_SCALE;
    fAcc_z = (float)acc_z/ACC_SCALE;
    activity =(ALPHA * activity) + (1-ALPHA) * sqrt(fAcc_x* fAcc_x + fAcc_y * fAcc_y + fAcc_z *fAcc_z);
    tmpSec = GetCurtSec();
    if(tmpSec != bufSec)
    {
      flagWr = 1;
    }
    bufSec = tmpSec;
    if((tmpSec%20 == 0)  && (flagWr))
    { 
      flagWr = 0;
      sprintf(data,"{\"usrId\":\"test_1\",\"dogName\":\"dog_1\",\"activity\":%f}", activity);
	  printf("%d %f %s",tmpSec,activity,data);
	  parseSendRequest(client, "POST", "/classes/iot_dog",data, NULL);
      printf("\n upload \n");
    }
  }
}
