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
	   //����1��PC���ڹ��߿���ģʽ
 	   while(RI)
	   {
		 RI=0;
		 temp=SBUF;
		 SendDataByUart1(temp);
		 commandparser(temp);
	   } 


	//����2���ֻ�app����ģʽ
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