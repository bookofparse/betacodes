#include <stdio.h>
#include <wiringPi.h>
#include <mcp23017.h>

int main (void)
{
  int i, bit ;

  wiringPiSetup () ;
  mcp23017Setup (100, 0x20) ;

  printf ("test I/O expander MCP23017 \n") ;

  for (i = 0 ; i < 4 ; ++i)
    pinMode (100 + i, OUTPUT) ;

  pinMode         (100 + 5, INPUT) ;
  pullUpDnControl (100 + 5, PUD_OFF) ;
 
  for (;;)
  {
    for (bit = 0 ; bit < 4 ; ++bit)
      digitalWrite (100 + bit, 1) ;
    delay (1000) ;
    for (bit = 0 ; bit < 4 ; ++bit)
      digitalWrite (100 + bit, 0) ;
    delay (1000) ;

    if(digitalRead (100 + 5) == 0)
    {
       printf("sw = 0 \n");
    }	
  }
  return 0 ;
}
