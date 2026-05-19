/*
 * led.h
 *
 *  Created on: May 17, 2026
 *      Author: DUC TAN
 */

#ifndef LED_H_
#define LED_H_
#include<stdint.h>

typedef enum{
	ON_LED,
	OFF_LED
}led_state;

typedef enum{
	GREEN_LED,
	ORANGE_LED,
	RED_LED,
	BLUE_LED
}led_t;

void LED_Init(void);
void LedCtrl(led_t led, led_state state);
void LedToggle(led_t led);

#endif /* LED_H_ */
