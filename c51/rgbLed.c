#include "rgbled.h"
#include "delay.h"

int duration = 20;
int count = 5;

void led_white()
{
    v = 1;
	r = 0;
	g = 0;
	b = 0;
}

void led_red()
{
    v = 1;
	r = 0;
	g = 1;
	b = 1;
}

void led_green()
{
    v = 1;
	r = 1;
	g = 0;
	b = 1;
}

void led_blue()
{
    v = 1;
	r = 1;
	g = 1;
	b = 0;
}

void led_red_green()
{
    v = 1;
	r = 0;
	g = 0;
	b = 1;
}

void led_red_blue()
{
    v = 1;
	r = 0;
	g = 1;
	b = 0;
}

void led_green_blue()
{
    v = 1;
	r = 1;
	g = 0;
	b = 0;
}

void led_none()
{
    v = 1;
	r = 1;
	g = 1;
	b = 1;
}

void led_off()
{
    v = 0;
	r = 0;
	g = 0;
	b = 0;
}

void flowing_water_light()
{
 
  // while(count--)
  // {
   	  led_white();
	  delayms(duration);
	  led_red();
	  delayms(duration);
	  led_green();
	  delayms(duration);
	  led_blue();
	  delayms(duration);
	  led_red_green();
	  delayms(duration);
	  led_red_blue();
	  delayms(duration);
	  led_green_blue();
	  delayms(duration);
	  led_none();
	  delayms(duration);
 //  }

}







