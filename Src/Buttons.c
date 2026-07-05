/*
 * Buttons.c
 *
 *  Created on: Jun 3, 2026
 *      Author: libak
 */
// using PA7 PA8 PB4
#include <Registers.hpp>
#include "Delay.h"

void init_clock()
{
    RCC_AHB1ENR |= (1U << 1) | (1U << 2) | (1U<<0); // Enable GPIOA (bit 0) GPIOB (bit 1) and GPIOC (bit 2)
    RCC_APB1ENR |= (1U << 18);            // Enable USART3 (bit 18)
}

void init_buttons(GPIO_TypeDef* gpio, uint8_t pin)
{
	gpio->MODER &= ~(3 << (pin*2)); // shifts the bits to where and PA7 are then clears them

	gpio->PUPDR &= ~(3 << (pin*2));
	gpio->PUPDR |= (1 << (pin*2));// pull up reg setting it to 01 for pull up we want the button to be high when not pressed
}

void init_on_board_led(GPIO_TypeDef* gpio, uint8_t pin){
	gpio->MODER &= ~(3 << pin*2);  // Clear bits 10 and 11 (led)
	gpio->MODER |=  (1 << pin*2);  // Set bit 10 to 1 (01 = Output)

}

