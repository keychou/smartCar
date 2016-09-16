/**********************
�ļ����ƣ�Led.c
���ߣ�Jellina����
˵�������д���1����2���Ե�����

***********************/

/**********************
����STC15F2K60S2ϵ�е�Ƭ��C���Ա��ʵ��
ʹ������ͷ�ļ������������ٰ���"REG51.H"
#include "STC15F2K60S2.H" 
***********************/
#include "serial.h"
#include "delay.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 11059200L		//����Ƶ�� �ر���ʾ����鿪����ľ���Ƶ���Ƿ���趨��Ƶ��һ��
#define BAUD 9600			// ������
#define TM (65536 - (FOSC/4/BAUD))		 
bit busy;
BYTE temp;

#define S2RI 0x01
#define S2TI 0x02

/*
*  ����1�� ���͵����ֽ�
*/
void SendDataByUart1(BYTE dat)
{
	while(busy);
	ACC=dat;
	busy=1;
	SBUF=ACC;
}

/*
* ����1�� �����ַ���
*/
void SendStringByUart1(char *s)
{
	while(*s)
	{
		SendDataByUart1(*s++);
	}
}

/*
  ����1�� �жϷ������
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
* ����1�� ���ڳ�ʼ��
*/
void uart1_init()
{			  			
	AUXR=0X00;   //��ʱ��1��Ϊ����1�Ĳ����ʷ�����
	SCON=0x50;	 //����1�Ŀ��ƼĴ����� �����ڷ�ʽ1
	TMOD=0x20;	 //��ʱ��1������ģʽ2�� 8λ�Զ���װ��ģʽ
	TH1=TL1=-(FOSC/12/32/BAUD);		 //��ͬ��TH1=TL1=256-(FOSC/12/32/BAUD);
	TR1=1;		 //��ʱ��1���ƼĴ���TCON�� ���п���λ
	ES=1;	 //CPU���ж���ɿ���λ
	EA=1;	 //�����жϿ���λ
}





void Uart2_Init(void)
{
	S2CON=0x50;
	T2L = TM; //���ò�������װֵ
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



