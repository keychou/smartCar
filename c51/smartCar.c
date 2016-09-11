#include "serial.h"
#include "delay.h"
#include "moto.h"
#include "pwm.h"

void main()
{
	uart1_init();
	Uart2_Init();
	pwm_config();
//	moto_side1(0, 3000);
//	moto_side2(0, 3000);

//	delayms(10000);
//	moto_side1(1, 2000);
//	moto_side2(1, 2000);

    while(1);
}  