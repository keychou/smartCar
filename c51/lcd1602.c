/**********************
作者：Jellina电子
说明：进行LCD1602测试的例程
***********************/

/**********************
基于STC15F2K60S2系列单片机C语言编程实现
使用如下头文件，不用另外再包含"REG51.H"
#include <STC15F2K60S2.h>
***********************/
//#include "reg51.h"
//sfr P4   = 0xC0;
#include <STC15F2K60S2.h>
#include "lcd1602.h"
#include "delay.h"

void lcd_wcom(uchar com)  //1602写命令函数                 
{ 
    rs=0;            //选择指令寄存器 
    rw=0;            //选择写 
    P2=com;            //把命令字送入P2 
    delay(5);            //延时一小会儿，让1602准备接收数据 
    en=1;           //使能线电平变化，命令送入1602的8位数据口 
    en=0; 
} 
void lcd_wdat(uchar dat)        //1602写数据函数       
{ 
    rs=1;        //选择数据寄存器 
    rw=0;        //选择写 
    P2=dat;        //把要显示的数据送入P2 
    delay(5);        //延时一小会儿，让1602准备接收数据 
    en=1;        //使能线电平变化，数据送入1602的8位数据口 
    en=0; 
} 
void lcd_init()              //1602初始化函数       
{ 
    lcd_wcom(0x38);       //8位数据，双列，5*7字形       
    lcd_wcom(0x0c);      //开启显示屏，关光标，光标不闪烁 
    lcd_wcom(0x06);    //显示地址递增，即写一个数据后，显示位置右移一位 
    lcd_wcom(0x01);    //清屏 
} 

void print_to_screen(uchar code table[])
{     
    uchar n,m=0; 

	lcdsel = 1;
    lcd_init();                 //液晶初始化 
    lcd_wcom(0x80);   //显示地址设为80H（即00H，）上排第一位       
    for(m=0;m<17;m++)     //将table[]中的数据依次写入1602显示 
    { 
            lcd_wdat(table[m]);           
            delay(200); 
    } 
//    lcd_wcom(0x80+0x44); //重新设定显示地址为0xc4,即下排第5位 
//    for(n=0;n<11;n++)   //将table1[]中的数据依次写入1602显示 
//    {     
//           lcd_wdat(table1[n]); 
//           delay(200); 
//    } 
    while(1);        //动态停机 
} 



