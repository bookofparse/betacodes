#include <wiringPi.h>
#include <stdio.h>
#define LED 7

int main(void)
{
  if(wiringPiSetup() == -1)
  {
    printf("Setup Error\n");
    return 1;
  }
  pinMode(LED, OUTPUT);
  while(1)
  {
    digitalWrite(LED, HIGH);
    delay (500);

    digitalWrite(LED, LOW);
    delay (500);
  }
  return 0;
}
