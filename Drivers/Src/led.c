/*
 * led.h
 *
 *  Created on: May 17, 2026
 *      Author: DUC TAN
 */

#include "led.h"

#define RCC_BASE_ADDR       	  0x40023800
#define GPIOD_BASE_ADDR           0x40020C00

void LED_Init(){
	uint32_t* GPIOD_MODER = (uint32_t*)GPIOD_BASE_ADDR;
	uint32_t* RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);
	*RCC_AHB1ENR |= 1 << 3;
	*GPIOD_MODER &= ~(0xFF << 24);
	*GPIOD_MODER |= 0b01 << 24;
	*GPIOD_MODER |= 0b01 << 26;
	*GPIOD_MODER |= 0b01 << 28;
	*GPIOD_MODER |= 0b01 << 30;
}

void LedCtrl(led_t led, led_state state){
	uint32_t* GPIOD_ODR = (uint32_t*)(GPIOD_BASE_ADDR + 0x14);
	if(state == ON_LED){
		*GPIOD_ODR |= (1 << (led + 12));
	}
	else{
		*GPIOD_ODR &= ~(1 << (led + 12));
	}
}

void LedToggle(led_t led){
	uint32_t* GPIOD_ODR = (uint32_t*)(GPIOD_BASE_ADDR + 0x14);
	*GPIOD_ODR ^= 1 << (led + 12);
}


