#ifndef UART_H_
#define UART_H_

#include <stdint.h> 
#include <string.h>  
#include <stdio.h> 
#include <stdarg.h> 

void UART_Init(void);
void UART_Send(char data);
void my_print(char* str, ...);
void print_float(float val);
#if 0
void USART1_IRQHandler(void);
void UART1_Callback(char recv_byte);
#endif

#endif /* UART_H_ */