/*
 * main.c
 *
 *  Created on: May 17, 2026
 *      Author: DUC TAN
 */
#include <string.h>
#include "led.h"
#include "button.h"
#include "tim1.h"
#include "exti0.h"
#include "uart.h"
#include "dma.h"
// #include "spi.h"
// #include "i2c.h"
// #include "adc.h"

void EXTI0_IT_Callback(){
	LedToggle(GREEN_LED);
}

char data[8];
#if 0
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
#endif

void DMA2_Receive_Callback(int recv_byte){
	if(recv_byte == 1){
		if(strstr(data, "ledon") != NULL){
			LedCtrl(ORANGE_LED, ON_LED);
		}
		else if(strstr(data, "ledoff") != NULL){
			LedCtrl(ORANGE_LED, OFF_LED);
		}
		recv_byte = 0;
	}
}


int main(){
	LED_Init();
	Button_Init();
	TIM1_Init();
	EXTI0Init();
	UART_Init();
	DMA2_Init(data);
	// SPI1_Init();
	// I2C1_Init();
	// ADC_Init();

	
	while(1){
		for(uint8_t speed = 0; speed <= 100; speed += 5)
        {
            TIM1_Set_Duty_Channel1(speed);
            Delay_ms(1000); 
        }
        
        for(uint8_t speed = 100; speed > 0; speed -= 5)
        {
            TIM1_Set_Duty_Channel1(speed);
            Delay_ms(1000);
        }
	}

	return 0;
}
