#include <wiringPi.h>
#include <stdio.h>

#define SW 8

void service_bt(void)
{
  printf("sw = 0 \n\r");
}

int main(void)
{
  wiringPiSetup();
  printf("test input\n\r");
  pullUpDnControl(SW, PUD_OFF);
  wiringPiISR (SW, INT_EDGE_FALLING, service_bt) ;
  while(1)
  {
    printf("IDLE\n\r");
    delay(3000);
  }
}
