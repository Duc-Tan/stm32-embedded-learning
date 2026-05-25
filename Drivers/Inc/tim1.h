/*
 * tim1.h
 *
 *  Created on: May 17, 2026
 *      Author: DUC TAN
 */

#ifndef TIM1_H_
#define TIM1_H_
#include<stdint.h>

void TIM1_Init();
void Delay_ms(int ms);
void TIM1_Set_Duty_Channel1(uint8_t duty_percent);

#endif /* TIM1_H_ */
