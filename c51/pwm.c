#include "pwm.h"
#include "serial.h"

void pwm_config()
{
/*
   ����PWM��ض˿�ģʽ
*/
	//��P1�ں�PWM��صĶ˿�����Ϊ׼˫���ģʽ��PWM6 = P1^6 , PWM7 = P1^7
	P1M0 &= ~0xc0;  
	P1M1 &= ~0xc0;

    //��P4�ں�PWM��صĶ˿�����Ϊ׼˫���ģʽ��PWM3_2 = P4^5, PWM4_2 = P4^4, PWM5_2 = P4^2
	P4M0 &= ~0x30;  
	P4M1 &= ~0x30;

/*
   ����PWM��ص����⹦�ܼĴ���
*/

//  ��չSFR���ʿ��ƹ���ʹ�ܣ��Ա����ǿ��Է���PWM��صļĴ����� ����رգ����޷�����PWM��ͷ�ļĴ���
	P_SW2 |= 0x80;


// ���� PWM2~7 ����˿�
 //   PWM3T1 = 3000;
//    PWM3T2 = 0;
	PWM3CR = 0x08;				//PWM3_2 = P4^5
	PWM4CR = 0x08;				//PWM4_2 = P4^4
	PWM6CR = 0x00;			    //PWM6 = P1^6
	PWM7CR = 0x00;				//PWM7 = P1^7


/*
    ����PWM2~7�������ʼ��ƽΪ0	, 
	note: ���������PWMxT1�� PWMxT2������£����۳�ʼ��ƽΪ0����1����Ӧ�Ķ˿ڵ�ѹ��Ϊvss/2, ������vss��0���������
*/
    PWMCFG |= 0x3f;

/* 
    PWMCR  PWM���ƼĴ���
	ENC7O ~ ENC2O
	0:  ����ΪGPIO��
	1�� ����ΪPWM����ڣ���PWM���ο��������ƣ�ע�⣺��ʱ���ֱ�Ӹ�IO�ڸ�ֵ��Ч�����磺P4^5 = 0 �� PWM3 = 0 ������������Ч
	����������PWM3,4,6,7ΪPWM�����
*/
    PWMCR = 0x36;

/*  
    ����PWM����
    PWMC PWM����������CYCLE�Ŀ�ʼ������������0ʱ���´�CYCLE��ʼ��������
    ���PWMxT1��PWMxT2ʹ�ü��ɿ���ռ�ձ�
	�����ʱCYCLE = 4096��PWMxT1 = 1024��PWM��ʼ��ƽΪ0����PWMC = 1024ʱ��PWM��ƽ��ת��ռ�ձ�Ϊ1/4 
*/
    PWMC = CYCLE;

//  ����PWMʱ��ѡ��Ĵ���
	PWMCKS = 0x00;

//	PWM3T1 = 3000;
//  ʹ��PWM�� ��ʼ����
    PWMCR |= 0x80;
	
}

void PWM3_setPwmWidth(int width)
{
   if (0 == width)
   {
      PWMCR &= ~0x02;
   	  PWM3 = 0;
   }else if (CYCLE == width)
   {
   	  PWMCR &= ~0x02;
	  PWM3 = 1;
   }else
   {  
      PWM3T1 = width;
	  PWMCR |= 0x02;
   }

}

void PWM4_setPwmWidth(int width)
{
   if (0 == width)
   {
      PWMCR &= ~0x04;
   	  PWM4 = 0;
   }else if (CYCLE == width)
   {
   	  PWMCR &= ~0x04;
	  PWM4 = 1;
   }else
   {  
      PWM4T1 = width;
	  PWMCR |= 0x04;
   }

}

void PWM6_setPwmWidth(int width)
{
   if (0 == width)
   {
      PWMCR &= ~0x10;
   	  PWM6 = 0;
   }else if (CYCLE == width)
   {
   	  PWMCR &= ~0x10;
	  PWM6 = 1;
   }else
   {  
      PWM6T1 = width;
	  PWMCR |= 0x10;
   }

}

void PWM7_setPwmWidth(int width)
{
   if (0 == width)
   {
      PWMCR &= ~0x20;
   	  PWM7 = 0;
   }else if (CYCLE == width)
   {
   	  PWMCR &= ~0x20;
	  PWM7 = 1;
   }else
   {  
      PWM7T1 = width;
	  PWMCR |= 0x20;
   }
}
