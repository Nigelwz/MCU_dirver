#ifndef _LPC_1830_H_
#define _LPC_1830_H_
#include "board.h"
void uart_init(LPC_USART_T *pUART);

void LPC_1830_UARTPutChar(char ch);

void for_uart_int(void);

void uart_handler(void);
#endif



