#include <stdio.h>
#include <errno.h>
#include <wiringPi.h>

#define M_A 12      //BCN_GPIO 10
#define M_B 4      //BCM_GPIO 23
#define M_nA 13       //BCM_GPIO 9
#define M_nB 5       //BCM_GPIO 24

void setStep(int inA, int inB, int innA, int innB)
{
  digitalWrite(M_A,inA);
  digitalWrite(M_B,inB);
  digitalWrite(M_nA,innA);
  digitalWrite(M_nB,innB);
}


int main(void)
{
  int i = 0;

  if(wiringPiSetup() == -1)
    return 1;
  pinMode(M_A,OUTPUT);
  pinMode(M_B,OUTPUT);
  pinMode(M_nA,OUTPUT);
  pinMode(M_nB,OUTPUT);
    
  for(i = 0; i < 360*4 ; i++)
  {
    setsteps(1,0,0,0);
    delay(10);
    setsteps(0,1,0,0);
    delay(10);
    setsteps(0,0,1,0);
    delay(10);
    setsteps(0,0,0,1);
    delay(10);
  }
  return 0;
}
