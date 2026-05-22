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
#include "uart.h"

void EXTI0_IT_Callback(){
	LedToggle(GREEN_LED);
}

char data[16] = {0};
int i = 0;
void UART1_Callback(char recv_byte){
	data[i] = recv_byte;
	if(data[i] == '\n'){
		data[i+1] = 0;
		if(strstr(data, "ledon\n") != NULL){
			LedCtrl(ORANGE_LED, ON_LED);
		}
		else if(strstr(data, "ledoff\n") != NULL){
			LedCtrl(ORANGE_LED, OFF_LED);
		}
		i = 0;
	} else {
		i++;
		if(i >= sizeof(data)-1) i = 0;
	}

}

int main(){
	LED_Init();
	Button_Init();
	TIM1_Init();
	EXTI0Init();
	UART_Init();

	while(1){
		LedCtrl(BLUE_LED, ON_LED);
		Delay_ms(1000);
		LedCtrl(BLUE_LED, OFF_LED);
		Delay_ms(1000);
	}

	return 0;
}
