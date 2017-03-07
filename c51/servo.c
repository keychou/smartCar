#include "servo.h"
#include "serial.h"
#include "delay.h"
#include "commandparser.h"
#include "moto.h"
#include "pwm.h"


#define FOSC 11059200L
#define T1MS (65536-(FOSC)/1000/10)

#define MAX_POSITION_H  25
#define MAX_POSITION_V  10
#define MIN_POSITION  5


sbit PWM_SERVO_V =P5^4;          //PWM信号输出
sbit PWM_SERVO_H =P5^5;          //PWM信号输出


unsigned char count_p = 0;
unsigned char SEV_conut = 5;
unsigned char SEH_count = 15;

unsigned char position_v = 5;
unsigned char position_h = 15;
unsigned char resolution = 2;

void tm0_isr() interrupt 1 using 1
{

//    PWM_SERVO_H = !PWM_SERVO_H ;
	if(count_p <= SEH_count) //控制占空比左右
    {
        //如果count的计数小于（5-25）也就是0.5ms-2.5ms则这段小t周期持续高电平。产生方波
        PWM_SERVO_H = 1;
    }
    else
    {
        PWM_SERVO_H = 0;
    }


	if(count_p <= SEV_conut) //控制占空比左右
    {
        //如果count的计数小于（5-25）也就是0.5ms-2.5ms则这段小t周期持续高电平。产生方波
        PWM_SERVO_V = 1;
    }
    else
    {
        PWM_SERVO_V = 0;
    }

	count_p++;
    if (count_p >= 200) //T = 20ms则定时器计数变量清0
    {
        count_p = 0;
    }
}

void Time0_Init()          //定时器初始化
{
    AUXR |= 0x80;
	TMOD = 0x00;
	TL0 = T1MS;
	TH0 = T1MS>>8;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}


void Time0_Init_1()          //定时器初始化
{
    AUXR |= 0x80;
	INT_CLKO = 0X01;
	TMOD &= 0xf0;
	TL0 = T1MS;
	TH0 = T1MS>>8;

	TR0 = 1;
	ET0 = 1;
	EA = 1;
}


void servo_h_increase(){
    if (position_h <= (MAX_POSITION_H - resolution)){
	   position_h += resolution;
	} else {
	   position_h = MAX_POSITION_H;
	}
	set_servo_h_position(position_h);
}

void servo_h_decrease(){
    if ((MIN_POSITION + resolution) <= position_h){
	   position_h -= resolution;
	} else {
	   position_h = MIN_POSITION;
	}
	set_servo_h_position(position_h);
}

void servo_v_increase(){
    if (position_v <= (MAX_POSITION_V - resolution)){
	   position_v += resolution;
	} else {
	   position_v = MAX_POSITION_V;
	}
	set_servo_v_position(position_v);
}

void servo_v_decrease(){
    if ((MIN_POSITION + resolution) <= position_v){
	   position_v -= resolution;
	} else {
	   position_v = MIN_POSITION;
	}
	set_servo_v_position(position_v);
}

void set_servo_h_position(int postion){
    send_string_by_uart1("set servo h position\r\n");
	if(MIN_POSITION < postion < MAX_POSITION_H){
	   SEH_count = postion;
	}
	else if (postion <= MIN_POSITION)
	{
		SEH_count = MIN_POSITION;
	}
	else if (postion >= MAX_POSITION_H)
	{
		SEH_count = MAX_POSITION_H;
	}

}


void set_servo_v_position(int postion){
    send_string_by_uart1("set servo v position\r\n");
    if(MIN_POSITION < postion < MAX_POSITION_V){
	   SEV_conut = postion;
	}
	else if (postion <= MIN_POSITION)
	{
		SEV_conut = MIN_POSITION;
	}
	else if (postion >= MAX_POSITION_V)
	{
		SEV_conut = MAX_POSITION_V;
	}
}