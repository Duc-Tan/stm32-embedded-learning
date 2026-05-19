/*
 * tim1.c
 *
 *  Created on: May 17, 2026
 *      Author: DUC TAN
 */
#include "tim1.h"

#define RCC_BASE_ADDR       	  0x40023800
#define TIM1_BASE_ADDR  		  0x40010000

void TIM1_Init(){
	uint16_t* ARR = (uint16_t*)(TIM1_BASE_ADDR + 0x2C);
	uint16_t* PSC = (uint16_t*)(TIM1_BASE_ADDR + 0x28);
	uint16_t* CR1 = (uint16_t*)TIM1_BASE_ADDR;
	uint16_t* TIM1_DIER = (uint16_t*)(TIM1_BASE_ADDR + 0x0C);
	uint32_t* RCC_APB2ENR = (uint32_t*)(RCC_BASE_ADDR + 0x44);
	*RCC_APB2ENR |= 1 << 0;
	//set ARR = 10
	*ARR = 10;
	//set PSC = 1599
	*PSC = 1599;
	*TIM1_DIER |= (1 << 0);
	uint32_t* ISER0 = (uint32_t*)0xE000E100;
	*ISER0 |= 1 << 25;
	//enable counter
	*CR1 |= 1;
}
int cnt;
void TIM1_UP_TIM10_IRQHandler(){
	uint16_t* TIM1_SR = (uint16_t*)(TIM1_BASE_ADDR + 0x10);
	*TIM1_SR &= ~(1 << 0);
	cnt++;
}

void Delay_ms(int ms){
	cnt = 0;
	while(ms >= cnt);
}

