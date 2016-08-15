#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <mcp23017.h>
	
#define MCP_ID 0x20


int fd;
int data = 0;

int main (void)
{
  int i, bit ;

  wiringPiSetup () ;
  mcp23017Setup (100, MCP_ID) ;
  fd = wiringPiI2CSetup(MCP_ID);


  printf ("test I/O expander MCP23017 \n") ;

  for (i = 0 ; i < 4 ; ++i)
    pinMode (100 + i, OUTPUT) ;

  pinMode         (100 + 5, INPUT) ;
  pullUpDnControl (100 + 5, PUD_OFF) ;
 
	
  printf ("LED ON \n") ;

  for (bit = 0 ; bit < 4 ; ++bit)
	digitalWrite (100 + bit, 1) ;
  for (i = 0 ; i <= 0x15 ; ++i)
  {
    data = wiringPiI2CReadReg8 (fd, i) ;
    printf("0x%d = 0x%x \n\r",i, data);
  }	
  printf ("LED OFF \n") ;

  for (bit = 0 ; bit < 4 ; ++bit)
	digitalWrite (100 + bit, 0) ;
	
  for (i = 0 ; i <= 0x15 ; ++i)
  {
	data = wiringPiI2CReadReg8 (fd, i) ;
	printf("0x%d = 0x%x \n\r",i, data);
  }	
  return 0 ;
}
