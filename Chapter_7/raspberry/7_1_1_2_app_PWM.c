#include <wiringPi.h>  //wiringPi.h
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>

#define OUTPIN 7

int main (int argc, char *argv[])
{
  if (wiringPiSetup() == -1) exit(1) ;  //init wiringPi

  pinMode(OUTPIN, OUTPUT) ;  //set the 0 pin as OUTPUT
  digitalWrite(OUTPIN, LOW) ;  //0 pin output LOW voltage
  softPwmCreate(OUTPIN, 0, 200) ;  //pwm initialize HIGH time 0, LOW time 200ms 
 
  printf("end: setup pwm\n");
  
  while(1) {
    printf("set 0.5mSec \n");
    softPwmWrite(OUTPIN, 5) ;
    delay(1000) ;
    printf("set 2.5mSec \n");
    softPwmWrite(OUTPIN, 25) ;
    delay(1000) ;
  }
  return 0 ;
}
