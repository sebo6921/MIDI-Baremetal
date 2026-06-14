/*
 * Buttons.c
 *
 *  Created on: Jun 3, 2026
 *      Author: libak
 */
// using PA7 PA8 PB4
#include "Registers.h"
#include "Delay.h"

void init_clock()
{
    RCC_AHB1ENR |= (1U << 1) | (1U << 2) | (1U<<0); // Enable GPIOA (bit 0) GPIOB (bit 1) and GPIOC (bit 2)
    RCC_APB1ENR |= (1U << 18);            // Enable USART3 (bit 18)
}

void init_buttons(){

	GPIOA_MODER &= ~(3 << (7*2)); // shifts the bits to where and PA7 are then clears them

	GPIOB_MODER &= ~(3 << (4*2)); // PB4
	GPIOA_MODER &= ~(3 << (8*2)); // PA8

	// On board LED PA5
	GPIOA_MODER &= ~(3 << 5*2);  // Clear bits 10 and 11 (led)
	GPIOA_MODER |=  (1 << 5*2);  // Set bit 10 to 1 (01 = Output)

	//PB4 and PA7 PA8
	GPIOB_PUPDR &= ~(3 << (4*2));  // clearing the bits for the pull up registor

	GPIOA_PUPDR &= ~(3 << (7*2));

	GPIOA_PUPDR &= ~(3 << (8*2));

	GPIOA_PUPDR |= (1 << (8*2));

	GPIOA_PUPDR |= (1 << (7*2));

	GPIOB_PUPDR |= (1 << (4*2));// pull up reg setting it to 01 for pull up we want the button to be high when not pressed
}

