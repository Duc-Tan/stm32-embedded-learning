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
void TIM1_UP_TIM10_IRQHandler();
void Delay_ms(int ms);

#endif /* TIM1_H_ */
