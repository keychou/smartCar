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
	   //����1��PC���ڹ��߿���ģʽ
 	   while(RI)
	   {
	     uchar temp;
		 RI=0;
		 temp=SBUF;
		 send_data_by_uart1(temp);
		 commandparser(temp);
	   } 


	   //����2���ֻ�app����ģʽ
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