#include "moto.h"
#include "pwm.h"
#include "serial.h"

#define INIT_SPEED 2000
int global_speed = INIT_SPEED;
/*
  ena：启动，停止
  direction: 车轮转向
  speed: 速度
*/
//moto_A and moto_C
void moto_side1(char direction, int speed)
{
    if (speed != 0)
	{
	   speed = global_speed;
	}

	if (speed > CYCLE)
	{
	   speed = CYCLE;
	}
    
	if (UP == direction)
	{  
		MOTOA1 = 0;
		MOTOA2 = 1;
		MOTOC1 = 0;
		MOTOC2 = 1; 
		PWM3_setPwmWidth(speed);
		PWM4_setPwmWidth(speed);

		    
	}else if (DOWN == direction)
	{
		MOTOA1 = 1;
		MOTOA2 = 0;
		MOTOC1 = 1;
		MOTOC2 = 0; 
		PWM3_setPwmWidth(speed);
		PWM4_setPwmWidth(speed);	
	}  
}

//moto_B and moto_D
void moto_side2(char direction, int speed)
{
    if (speed != 0)
	{
	   speed = global_speed;
	}
	
	if (speed > CYCLE)
	{
	   speed = CYCLE;
	}
    
	if (UP == direction)
	{
        MOTOB1 = 0;
		MOTOB2 = 1;
		MOTOD1 = 0;
		MOTOD2 = 1; 
		PWM6_setPwmWidth(speed);
		PWM7_setPwmWidth(speed);
		    
	}else if (DOWN == direction)
	{		
        MOTOB1 = 1;
		MOTOB2 = 0;
		MOTOD1 = 1;
		MOTOD2 = 0; 
		PWM6_setPwmWidth(speed);
		PWM7_setPwmWidth(speed);
	}
}


void set_speed_up(int speed){
    send_string_by_uart1("speed up\r\n");
    if (global_speed < (CYCLE - 500))
	{
	   global_speed =  global_speed + 500;
	} 
	else if ((CYCLE - 500) < global_speed)
	{
		global_speed =  CYCLE;
	}
}

void set_speed_down(int speed){
    send_string_by_uart1("speed down\r\n");
    if (global_speed >= 500)
	{
	   global_speed =  global_speed - 500;
	} 
	else if (global_speed < 500)
	{
		global_speed =  0;
	}
}