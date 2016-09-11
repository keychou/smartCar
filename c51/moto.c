#include "moto.h"
#include "pwm.h"

/*
  ena：启动，停止
  direction: 车轮转向
  speed: 速度
*/

//moto_A and moto_C
void moto_side1(char direction, int speed)
{

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