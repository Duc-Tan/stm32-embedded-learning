/*
 * tim1.c
 *
 *  Created on: May 17, 2026
 *      Author: DUC TAN
 */
#include "tim1.h"

#define RCC_BASE_ADDR       	  0x40023800
#define TIM1_BASE_ADDR  		  0x40010000
#define GPIOA_BASE_ADDR 		  0x40020000

void TIM1_Init(){
	uint16_t* ARR = (uint16_t*)(TIM1_BASE_ADDR + 0x2C);
	uint16_t* PSC = (uint16_t*)(TIM1_BASE_ADDR + 0x28);
	uint16_t* CR1 = (uint16_t*)TIM1_BASE_ADDR;
	uint16_t* TIM1_CCMR1 = (uint16_t*)(TIM1_BASE_ADDR + 0x18);
	uint16_t* TIM1_CCR1 = (uint16_t*)(TIM1_BASE_ADDR + 0x34);
	uint16_t* TIM1_CCER1 = (uint16_t*)(TIM1_BASE_ADDR +  0x20);
	uint16_t* TIM1_BDTR = (uint16_t*)(TIM1_BASE_ADDR +  0x44);
	uint32_t* GPIOA_MODER = (uint32_t*)(GPIOA_BASE_ADDR + 0x00);
	uint32_t* GPIOA_AFRH = (uint32_t*)(GPIOA_BASE_ADDR + 0x24);
	uint32_t* RCC_APB2ENR = (uint32_t*)(RCC_BASE_ADDR + 0x44);
	uint32_t* RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR +  0x30);

	*RCC_AHB1ENR |= 1 << 0;
	*GPIOA_MODER &= ~(0b11 << 16);
	*GPIOA_MODER |= 0b10 << 16;
	*GPIOA_AFRH &= ~(0xf << 0);
	*GPIOA_AFRH |= 0b0001 << 0;

	*RCC_APB2ENR |= 1 << 0;
	//set ARR = 1000
	*ARR = 1000;
	//set PSC = 16 - 1
	*PSC = 15;
	// config PWM mode 1
	*TIM1_CCMR1 &= ~(0b111 << 4);
	*TIM1_CCMR1 |= 0b110 << 4;
	*TIM1_CCMR1 |= 1 << 3;
	//set inital duty cycle
	*TIM1_CCR1 = 500;
	//enable channel 1
	*TIM1_CCER1 |= 1 << 0;
	//enable main output
	*TIM1_BDTR |= 1 << 15;
	//enable counter
	*CR1 |= 1;
}

void Delay_ms(int ms){
	uint16_t* TIM1_SR = (uint16_t*)(TIM1_BASE_ADDR + 0x10);
	for(int i = 0; i < ms; i++){
		while(((*TIM1_SR >> 0) & 1) == 0);
		*TIM1_SR &= ~(1 << 0);
	}
}



void TIM1_Set_Duty_Channel1(uint8_t duty_percent){
	uint16_t* TIM1_CCR1 = (uint16_t*)(TIM1_BASE_ADDR + 0x34);
	if (duty_percent > 100) 
		duty_percent = 100;
	uint32_t ccr_value = (duty_percent * 1000) / 100;
	*TIM1_CCR1 = ccr_value;
}

