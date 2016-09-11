

#define  uint unsigned int  
#define  uchar unsigned char 
sbit rs=P4^0;    //1602的数据/指令选择控制线 
sbit rw=P4^1;        //1602的读写控制线 
sbit en=P4^2;        //1602的使能控制线 

sbit lcdsel=P4^3;

/*口接1602的D0~D7，注意不要接错了顺序，我以前可在这上面吃过亏～*/ 

void lcd_wcom(uchar com);
void lcd_wdat(uchar dat);
void lcd_init();
void print_to_screen(uchar code table[]);