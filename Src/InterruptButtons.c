/*
 * Interrupt.c
 *
 *  Created on: Jun 4, 2026
 *      Author: libak
 */

#include "Registers.h"
#include "Delay.h"


void init_interrupt_buttons()
{
	// 1. Force GPIOA Pin 4 and Pin 7 into Input Mode (00)
	GPIOA_MODER &= ~(3U << (4 * 2)); // Clear bits 9:8 to set PA4 to Input
	GPIOA_MODER &= ~(3U << (7 * 2)); // Clear bits 15:14 to set PA7 to Input

	// 2. Map EXTI4 and EXTI7 lines specifically to Port A
	SYSCFG_EXTICR2 &= ~(0xF << 0);  // Clear bits 3:0 to map EXTI4 to Port A
	SYSCFG_EXTICR2 &= ~(0xF << 12); // Clear bits 15:12 to map EXTI7 to Port A

	EXTI_FTSR |= (1 << 4) | (1 << 7); // activating the  exti 4 and 7

	EXTI_IMR |= (1<<4) |(1<<7);
}
void init_interrupt_vector_table_bit()
{
	NVIC_ISER0 |= (1<<10) | (1<<23); // enable exti line 9-5 and exti line 4 bit
	NVIC_ISER1 |= (1<<7); // enable uart3 bit for interrupt
}

void init_interrupt_clocks()
{
	RCC_APB2ENR |= (1U<<14); // turn on the clock for the interrupt
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

