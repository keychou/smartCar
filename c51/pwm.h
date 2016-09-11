#include "stc15f2k60s2.h" 


//PWM 端口设置
//sbit PWM2 = P3^7;	   // pwm2
//sbit PWM2 = P2^7;	   // pwm2_2，此端口被 1602/12864 占据
//sbit PWM3 = P2^1;	   // pwm3  , 此端口被 1602/12864 占据
sbit PWM3 = P4^5;	   // pwm3_2, moto A
//sbit PWM4 = P2^2;	   // pwm4  , 此端口被 1602/12864 占据
sbit PWM4 = P4^4;	   // pwm4_2, moto B
//sbit PWM5 = P2^3;	   // pwm5  , 此端口被 1602/12864 占据
//sbit PWM5 = P4^2;	   // pwm5_2, 此端口被 1602/12864 占据
sbit PWM6 = P1^6;	   // pwm6  , moto C
//sbit PWM6 = P0^7;	   // pwm6_2, 
sbit PWM7 = P1^7;	   // pwm7  , moto D
//sbit PWM7 = P0^6;	   // pwm7_2



//PWM周期
#define CYCLE 4096

void pwm_config();
void PWM3_setPwmWidth(int width);
void PWM4_setPwmWidth(int width);
void PWM6_setPwmWidth(int width);
void PWM7_setPwmWidth(int width);

 