

#define  uint unsigned int  
#define  uchar unsigned char 
sbit rs=P4^0;    //1602������/ָ��ѡ������� 
sbit rw=P4^1;        //1602�Ķ�д������ 
sbit en=P4^2;        //1602��ʹ�ܿ����� 

sbit lcdsel=P4^3;

/*�ڽ�1602��D0~D7��ע�ⲻҪ�Ӵ���˳������ǰ����������Թ�����*/ 

void lcd_wcom(uchar com);
void lcd_wdat(uchar dat);
void lcd_init();
void print_to_screen(uchar code table[]);