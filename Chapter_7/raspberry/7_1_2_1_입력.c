#include<wiringPi.h>
#include<stdio.h>

#define SW 8

int main(void)
{
  wiringPiSetup();
  printf("test input\n\r");
  pinMode(SW, INPUT);
  pullUpDnControl(SW, PUD_UP);

while(1)
{
  if(digitalRead(SW) == 0)
    printf("SW == 0\n\r");
  printf("IDLE \n\r");
  delay(3000);
}
}
