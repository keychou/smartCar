#include "pwm.h"
#include "serial.h"

void pwm_config()
{
/*
   设置PWM相关端口模式
*/
	//将P1口和PWM相关的端口设置为准双向口模式：PWM6 = P1^6 , PWM7 = P1^7
	P1M0 &= ~0xc0;  
	P1M1 &= ~0xc0;

    //将P4口和PWM相关的端口设置为准双向口模式：PWM3_2 = P4^5, PWM4_2 = P4^4, PWM5_2 = P4^2
	P4M0 &= ~0x30;  
	P4M1 &= ~0x30;

/*
   设置PWM相关的特殊功能寄存器
*/

//  扩展SFR访问控制功能使能，以便我们可以访问PWM相关的寄存器， 如果关闭，则无法操作PWM开头的寄存器
	P_SW2 |= 0x80;


// 设置 PWM2~7 输出端口
 //   PWM3T1 = 3000;
//    PWM3T2 = 0;
	PWM3CR = 0x08;				//PWM3_2 = P4^5
	PWM4CR = 0x08;				//PWM4_2 = P4^4
	PWM6CR = 0x00;			    //PWM6 = P1^6
	PWM7CR = 0x00;				//PWM7 = P1^7


/*
    设置PWM2~7的输出初始电平为0	, 
	note: 如果不设置PWMxT1或 PWMxT2的情况下，无论初始电平为0还是1，相应的端口电压都为vss/2, 而不是vss或0，待解决！
*/
    PWMCFG |= 0x3f;

/* 
    PWMCR  PWM控制寄存器
	ENC7O ~ ENC2O
	0:  设置为GPIO口
	1： 设置为PWM输出口，受PWM波形控制器控制，注意：此时如何直接给IO口赋值无效，比如：P4^5 = 0 或 PWM3 = 0 这样的命令无效
	下面是设置PWM3,4,6,7为PWM输出口
*/
    PWMCR = 0x36;

/*  
    设置PWM周期
    PWMC PWM计数器，从CYCLE的开始倒计数，减到0时重新从CYCLE开始倒计数。
    配合PWMxT1，PWMxT2使用即可控制占空比
	假如此时CYCLE = 4096，PWMxT1 = 1024，PWM初始电平为0，则PWMC = 1024时，PWM电平跳转，占空比为1/4 
*/
    PWMC = CYCLE;

//  设置PWM时钟选择寄存器
	PWMCKS = 0x00;

//	PWM3T1 = 3000;
//  使能PWM， 开始计数
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
