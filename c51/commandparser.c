#include "commandparser.h"
#include "moto.h"
#include "pwm.h"
#include "serial.h"

#define UP 0x57     // W
#define DOWN 0x53   // S
#define LEFT 0x41   // A
#define RIGHT 0x44  // D

#define STOP 0x50   // P




void commandparser(unsigned char cmd)
{
   SendStringByUart1("cmd = ");
   SendDataByUart1(cmd);
   SendStringByUart1("\r\n");

   switch (cmd)
   {
       case 'W':
	      SendStringByUart1("car UP\r\n");
		  moto_side1(0, 2000);
          moto_side2(0, 2000);
	      break;
	   case 'S':
	      SendStringByUart1("car DOWN\r\n");
		  moto_side1(1, 2000);
          moto_side2(1, 2000);
	      break;
	   case 'A':
	      SendStringByUart1("car LEFT\r\n");
	      moto_side1(1, 2000);
		  moto_side2(0, 2000);
	      break;
       case 'D':
	      moto_side1(0, 2000);
		  moto_side2(1, 2000);
		  SendStringByUart1("car RIGHT\r\n");
	      break;
	   case 'P':
	      SendStringByUart1("car STOP\r\n");
	      moto_side1(0, 0);
          moto_side2(0, 0);
   		  break;
	   default:
	      SendStringByUart1("cmd not found\r\n");
	      break;
   }
}



