#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <mcp23017.h>

#define MCP_ID 0x20
#define INT_PIN 7


int fd;
int data = 0;

void service_INT(void)
{
	static int i = 0;

  data = wiringPiI2CReadReg8 (fd, 0x10) ;
  if( data&0x20 == 0x20 )
	  printf("INT sw = 0 : %d \n",i++);

}

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
  pullUpDnControl(INT_PIN, PUD_OFF);
  wiringPiISR (INT_PIN, INT_EDGE_FALLING, service_INT) ;
  wiringPiI2CWriteReg8  (fd, 0x04, 0x20) ;

  for (i = 0 ; i <= 0x15 ; ++i)
  {
	data = wiringPiI2CReadReg8 (fd, i) ;
	printf("0x%x : 0x%x \n\r",i,data);
  }	

  for (;;)
  {
    wiringPiI2CWriteReg8  (fd, 0x12, 0x0f) ;
    delay (1000) ;
    wiringPiI2CWriteReg8  (fd, 0x12, 0x00) ;
    delay (1000) ;
  }
  return 0 ;
}
