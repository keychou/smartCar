#ifndef __MOTO_H_
#define __MOTO_H_
#include "stc15f2k60s2.h"


//宏定义布尔类型

#define UP 0
#define DOWN 1

sbit MOTOA1 = P0^0;
sbit MOTOA2 = P0^1;
sbit MOTOB1 = P0^2;
sbit MOTOB2 = P0^3;
sbit MOTOC1 = P0^4;
sbit MOTOC2 = P0^5;
sbit MOTOD1 = P1^2;
sbit MOTOD2 = P1^3;

void moto_side1(char direction, int speed);
void moto_side2(char direction, int speed);
void set_speed_up(int speed);
void set_speed_down(int speed);


#endif