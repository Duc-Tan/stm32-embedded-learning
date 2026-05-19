/*
 * main.c
 *
 *  Created on: May 17, 2026
 *      Author: DUC TAN
 */

#include "led.h"
#include "button.h"
#include "tim1.h"
#include "exti0.h"

void EXTI0_IT_Callback(){
	LedToggle(GREEN_LED);
}

int main(){
	LED_Init();
	Button_Init();
	TIM1_Init();
	EXTI0Init();

	while(1){
		LedCtrl(BLUE_LED, ON_LED);
		Delay_ms(1000);
		LedCtrl(BLUE_LED, OFF_LED);
		Delay_ms(1000);
	}

	return 0;
}

void SystemInit(){
	
}
