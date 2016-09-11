/**********************
文件名称：Led.c
作者：Jellina电子
说明：进行串口1串口2测试的例程

***********************/

/**********************
基于STC15F2K60S2系列单片机C语言编程实现
使用如下头文件，不用另外再包含"REG51.H"
#include "STC15F2K60S2.H" 
***********************/
#include "serial.h"
#include "delay.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 11059200L		//晶振频率 特别提示：检查开发板的晶振频率是否和设定的频率一致
#define BAUD 9600			// 波特率
#define TM (65536 - (FOSC/4/BAUD))		 
bit busy;
BYTE temp;

#define S2RI 0x01
#define S2TI 0x02

/*
*  串口1： 发送单个字节
*/
void SendDataByUart1(BYTE dat)
{
	while(busy);
	ACC=dat;
	busy=1;
	SBUF=ACC;
}

/*
* 串口1： 发送字符串
*/
void SendStringByUart1(char *s)
{
	while(*s)
	{
		SendDataByUart1(*s++);
	}
}

/*
  串口1： 中断服务程序
*/
void Uart1() interrupt 4 using 1
{
	if(RI)
	{
		RI=0;
		temp=SBUF;
		SendDataByUart1(temp);
	    delay(8);
	}
	if(TI)
	{
		TI=0;  		
		busy=0;
	}
}

/*
* 串口1： 串口初始化
*/
void uart1_init()
{			  			
	AUXR=0X00;   //定时器1作为串口1的波特率发生器
	SCON=0x50;	 //串口1的控制寄存器， 工作于方式1
	TMOD=0x20;	 //定时器1工作在模式2： 8位自动重装载模式
	TH1=TL1=-(FOSC/12/32/BAUD);		 //等同于TH1=TL1=256-(FOSC/12/32/BAUD);
	TR1=1;		 //定时器1控制寄存器TCON， 运行控制位
	ES=1;	 //CPU总中断许可控制位
	EA=1;	 //串口中断控制位
}





void Uart2_Init(void)
{
	S2CON=0x50;
	T2L = TM; //设置波特率重装值
	T2H = TM>>8;
	AUXR|=0X14;	   
	IE2=0x01;
	EA=1;
}

void Uart2() interrupt 8 using 1
{
	if(S2CON & S2RI)
	{
		S2CON &= ~S2RI;
		temp=S2BUF;
		SendDataByUart1(temp);
		delay(8);			   

	}
	if(S2CON & S2TI)
	{
		S2CON &= ~S2TI;
		busy=0;
	}
}
void SendDataByUart2(BYTE dat)
{
	while(busy);
	ACC=dat;
	busy = 1;
	S2BUF=ACC;
}

void SendStringByUart2(char *s)
{
	while(*s)
	{
		SendDataByUart2(*s++);
	}
}



