/*
 * Interrupt.c
 *
 *  Created on: Jun 4, 2026
 *      Author: libak
 */

#include <Registers.hpp>
#include "Delay.h"
#include "UART.h"
// we have programmed PB4 and PA7 and PA8 as buttons for this MIDI

void init_interrupt_buttons()
{
	// SYSCFG_EXTICR2 maps to bits 4-7
	// SYSCFG_EXTICR3 maps to bits 8-11
	// EXTI7 == PA7 lies on bit 12-15 so need clear them
	SYSCFG_EXTICR2 &= ~(0xF << 0);  // Clear bits 3:0 to map EXTI4 to Port A
	SYSCFG_EXTICR2 |= (0x01  << 0); //  set bits 0:3 to 0001 to map EXTI4 to Port B

	SYSCFG_EXTICR2 &= ~(0xF << 12); // Clear bits 15:12 and set bits 12:15 to 0000 to map EXTI7 to Port A

	SYSCFG_EXTICR3 &= ~(0xF << 0); //  Clear bits 0:3 and set bits 0:3 to 0000 to map EXTI8 to Port B

	//tells the hardware to watch for a falling edge signal on Lines 4, 7, and 8.
	EXTI_FTSR |= (1 << 4) | (1 << 7) | (1 << 8);

	//unmasks (enables/unmutes) the interrupt channels for Lines 4, 7, and 8.
	EXTI_IMR |= (1<<4) |(1<<7) | (1 << 8);
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

void EXTI4_IRQHandler( )
{
	 if ((EXTI_PR & (1 << 4)))
		{
		 	EXTI_PR |= (1<<4);
			GPIOA->ODR ^= (1 << 5);  // Turn ON onboard LED
			delay_cycles(320000);
		}
}

void EXTI9_5_IRQHandler()
{
	// having print statments inside here will lock up program
	if((EXTI_PR & (1 << 7)))
		{
			EXTI_PR |= (1<<7);
			GPIOA->ODR ^= (1 << 5);  // Turn ON onboard LED
			delay_cycles(320000);

		}
	if((EXTI_PR & (1 << 8)))
			{
				EXTI_PR |= (1<<8);
				GPIOA->ODR ^= (1 << 5);  // Turn ON onboard LED
				delay_cycles(320000);
			}
}

