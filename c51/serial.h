#include "stc15f2k60s2.h" 
#include "intrins.h"
#include "common.h"

void SendDataByUart1(BYTE dat);
void SendStringByUart1(char *s);
void uart1_init();
void Uart2_Init(void);
void SendDataByUart2(BYTE dat);
void SendStringByUart2(char *s);
