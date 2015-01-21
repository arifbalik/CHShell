#ifndef CHSHELL_USART_H
#define CHSHELL_USART_H

#include <misc.h>	

#define MAX_STRLEN 120 

extern volatile char received_string[MAX_STRLEN+1]; // this will hold the recieved string
extern int buffer_flag;



extern void CHTerminalPrint(char* data);
extern void Delay(__IO uint32_t nCount);
extern void clear_buffer(void);
extern void init_USART1(uint32_t baudrate);


#endif
