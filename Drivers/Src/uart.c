#include "uart.h"

#define UART1_BASE_ADDR			  0x40011000
#define GPIOB_BASE_ADDR 		  0x40020400
#define RCC_BASE_ADDR       	  0x40023800

void UART_Init(){  
	uint32_t* GPIOB_MODER = (uint32_t*)(GPIOB_BASE_ADDR + 0x00);
	uint32_t* GPIOB_AFRL = (uint32_t*)(GPIOB_BASE_ADDR + 0x20);
	uint32_t* UART1_CR1 = (uint32_t*)(UART1_BASE_ADDR + 0x0C);
	uint32_t* UART1_BRR = (uint32_t*)(UART1_BASE_ADDR + 0x08);
	uint32_t* UART1_CR3 = (uint32_t*)(UART1_BASE_ADDR +  0x14);
	uint32_t* RCC_APB2ENR = (uint32_t*)(RCC_BASE_ADDR + 0x44);
	uint32_t* RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);

	/*IO port B clock enable*/
	*RCC_AHB1ENR |= 1 << 1;
	/* Set PB3, PB6 as alternate function mode */
	*GPIOB_MODER &= ~((0b11 << 6) | ((0b11 << 12)));
	*GPIOB_MODER |= (0b10 << 6) | (0b10 << 12);

	/* PB3, PB6 select AF07*/
	*GPIOB_AFRL &= ~((0b1111 << 12) | (0b1111 << 24));
	*GPIOB_AFRL |= (0b0111 << 12) | (0b0111 << 24); // PB3: RX, PB6: TX

	/*USART1 clock enable*/
	*RCC_APB2ENR |= 1 << 4;
	/* Word length */
	*UART1_CR1 &= ~(1 << 12);
	/* Set baudrate */
	*UART1_BRR = (104 << 4) | 3;
	/* Transmitter enable */
	*UART1_CR1 |= (1 << 3);
	/* Receiver enable */
	*UART1_CR1 |= (1 << 2);
	/* UART1 enable */
	*UART1_CR1 |= (1 << 13);
	#if 0
	/* Enable interrupt UART1 */
	*UART1_CR1 |= (1 << 5);
	uint32_t* ISER1 = (uint32_t*)0xE000E104;
	*ISER1 |= (1 << 5);
	#endif
	/* DMA enable receiver */
	*UART1_CR3 |= 1 << 6;
}

void UART_Send(char data){
	uint32_t* UART_DR = (uint32_t*)(UART1_BASE_ADDR + 0x04);
	uint32_t* UART_SR = (uint32_t*)(UART1_BASE_ADDR + 0x00);
	while(((*UART_SR >> 7) & 1) == 0);
	*UART_DR = data;
	while(((*UART_SR >> 6) & 1) == 0);
}

void my_print(char* str, ...){
	va_list list;
    va_start(list, str);
	char print_buf[128] = {0};
	vsprintf(print_buf, str, list);
	int len = strlen(print_buf);
	for(int i = 0; i < len; i++){
		UART_Send(print_buf[i]);
	}
	va_end(list);
}
#if 0
char rx_buf;
void USART1_IRQHandler(){
	uint32_t* UART1_DR = (uint32_t*)(UART1_BASE_ADDR + 0x04);
	uint32_t* UART1_SR = (uint32_t*)(UART1_BASE_ADDR + 0x00);
    if(((*UART1_SR >> 5) & 1) == 1){
		rx_buf = (char)*UART1_DR;
		UART1_Callback(rx_buf);
	}
}

__attribute__((weak)) void UART1_Callback(char recv_byte){
    
}
#endif