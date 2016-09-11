#include "delay.h"

void delayms(unsigned int n)
{
  int i = 10;
  while(--i)
  {
  	  while(--n);
  } 
}


void delay(unsigned int  n)       //ÑÓÊ±º¯Êý                       
{ 
    unsigned int x,y;  
    for(x=n;x>0;x--) 
        for(y=110;y>0;y--); 
} 