/*
 * exti0.h
 *
 *  Created on: May 18, 2026
 *      Author: DUC TAN
 */

#ifndef EXTI0_H_
#define EXTI0_H_
#include<stdint.h>

void EXTI0Init(void);
void EXTI0_IRQHandler(void);
void EXTI0_IT_Callback(void);

#endif /* EXTI0_H_ */
