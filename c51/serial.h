#include "stc15f2k60s2.h" 
#include "intrins.h"
#include "common.h"

void send_data_by_uart1(uchar dat);
void send_string_by_uart1(char *s);
void uart1_init();
void uart2_init(void);
void send_data_by_uart2(uchar dat);
void send_string_by_uart2(char *s);
