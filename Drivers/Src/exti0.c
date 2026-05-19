/*
 * exti0.c
 *
 *  Created on: May 18, 2026
 *      Author: DUC TAN
 */
#include "exti0.h"

#define EXTI_BASE_ADDR 			  0x40013C00

void EXTI0Init(){
	//set rising and falling
	uint32_t *EXTI_RISING = (uint32_t*) (EXTI_BASE_ADDR + 0x08);
	uint32_t *EXTI_FALLING = (uint32_t*) (EXTI_BASE_ADDR + 0x0C);
	*EXTI_RISING |= 1;
	*EXTI_FALLING |= 1;
	//set interrupt mask
	uint32_t *EXTI_INTERRUPT_MASK = (uint32_t*) (EXTI_BASE_ADDR + 0x00);
	*EXTI_INTERRUPT_MASK |= 1;
	//set NVIC accept interrupt signal
	uint32_t *NVIC_ISER0 = (uint32_t*) 0xE000E100;
	*NVIC_ISER0 |= (1 << 6);
}

void EXTI0_IRQHandler() {
	uint32_t* EXTI_PR = (uint32_t*)(EXTI_BASE_ADDR +  0x14);
	*EXTI_PR |= 0b01;
	EXTI0_IT_Callback();
}

__attribute__((weak)) void EXTI0_IT_Callback(){

}

