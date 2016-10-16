#include "serial.h"
#include "delay.h"
#include "moto.h"
#include "pwm.h"
#include "commandparser.h"

#define S2RI 0x01
#define S2TI 0x02

void main()
{
    uart1_init();
	uart2_init();
	pwm_config();
	while(1)
	{	
	   //串口1，PC串口工具控制模式
 	   while(RI)
	   {
	     uchar temp;
		 RI=0;
		 temp=SBUF;
		 send_data_by_uart1(temp);
		 commandparser(temp);
	   } 


	   //串口2，手机app控制模式
  	   if(S2CON & S2RI)
	   {
	     uchar temp;
		 S2CON &= ~S2RI;
		 temp=S2BUF;
		 send_data_by_uart1(temp);
		 commandparser(temp); 		  
	   }
	}
}  