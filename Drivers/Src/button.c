/*
 * button.c
 *
 *  Created on: May 17, 2026
 *      Author: DUC TAN
 */
#include "button.h"

#define RCC_BASE_ADDR       	  0x40023800
#define GPIOA_BASE_ADDR 		  0x40020000

void Button_Init(){
	uint32_t* GPIOA_MODER = (uint32_t*)GPIOA_BASE_ADDR;
	uint32_t* RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);
	*RCC_AHB1ENR |= 1 << 0;
	*GPIOA_MODER &= ~(0b11 << 0);
}

char ButtonGetState(){
	uint32_t* GPIOA_IDR = (uint32_t*)(GPIOA_BASE_ADDR + 0x10);
	if(((*GPIOA_IDR >> 0) & 1) == 1)
		return 1;
	else
		return 0;
}





