/*
 * Interrupt.c
 *
 *  Created on: Jun 4, 2026
 *      Author: libak
 */

#include "Registers.h"
#include "Delay.h"

void init_interrupt()
{
	RCC_APB2ENR |= (1U<<14); // turn on the clock for the interrupt

	SYSCFG_EXTICR2 &= ~(0xF << 0);
	// Clear bits 15:12 to map EXTI7 to Port A

	SYSCFG_EXTICR2 &= ~(0xF << 12);

	EXTI_FTSR |= (1 << 4); // activating the  exti 4 and 7
	EXTI_FTSR |= (1 << 7);

	EXTI_IMR |= (1<<4) |(1<<7);

	NVIC_ISER0 |= (1<<10) | (1<<23);
}

void EXTI4_IRQHandler()
{
	 if ((EXTI_PR & (1 << 4)))
		{
		 	EXTI_PR |= (1<<4);
			GPIOA_ODR ^= (1 << 5);  // Turn ON onboard LED
			delay_cycles(320000);
		}
}

void EXTI9_5_IRQHandler()
{
	if((EXTI_PR & (1 << 7)))
		{
			EXTI_PR |= (1<<7);
			GPIOA_ODR ^= (1 << 5);  // Turn ON onboard LED
			delay_cycles(320000);
		}
}
