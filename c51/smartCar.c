#include "serial.h"
#include "delay.h"
#include "moto.h"
#include "pwm.h"
#include "commandparser.h"

unsigned char temp;

#define S2RI 0x01
#define S2TI 0x02

void main()
{
//	uart1_init();
//	Uart2_Init();
//	pwm_config();
//	SendStringByUart1("start\r\n");
//
//    while(1){
//	  while(RI)
//	  {
//		 RI=0;
//	     temp=SBUF;
//		 SendDataByUart1(temp);
//		 //commandparser(temp);
//	  }
//	}


    uart1_init();
	Uart2_Init();
	pwm_config();
	while(1)
	{	
	   //串口1，PC串口工具控制模式
 	   while(RI)
	   {
		 RI=0;
		 temp=SBUF;
		 SendDataByUart1(temp);
		 commandparser(temp);
	   } 


	//串口2，手机app控制模式
  	if(S2CON & S2RI)
	{
	    BYTE temp;
		S2CON &= ~S2RI;
		temp=S2BUF;
		SendDataByUart1(temp);
		commandparser(temp); 
	//	delay(2);		  
	}
	}
}  