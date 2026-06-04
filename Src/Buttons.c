/*
 * Buttons.c
 *
 *  Created on: Jun 3, 2026
 *      Author: libak
 */
// using 3 and 4 and 1
#include "Registers.h"
#include "Delay.h"

void init_clock(){
	RCC_AHB1ENR |=(1U<<0);
	RCC_APB2ENR |=(1U<<0);
}
unsigned int read_potentiometer(void)
{
    // HERE is where you use it!
    // We loop and do nothing until Bit 1 (EOC) of the status register turns into a 1.
    while (!(ADC_SR1 & (1 << 1)))
    {
        // Waiting for the hardware to finish the current sample...
    }

    // Once it's ready, we grab the value out of the data register
    return ADC_DR1;
}

void potention_meter_init()
{
	GPIOA_MODER &= ~((3<<1*2)); // clear and shift the bits PA1 since we clear we make them 00 which is teh same as input mode
	GPIOA_MODER |= (3<<1*2);
	GPIOA_PUPDR &= ~(3 << 1*2); // make the bits 11 which is analog input
	RCC_APB2ENR |= (1<<8); // turn on the adc1
	ADC_SQR3 = 1; // assign pa1 to the adc register
	ADC_CR2 |= (1U<<0);
	ADC_CR2 |= (1U<<1);

	delay_cycles(10000);
	ADC_CR2 |= (1U<<30);
}


void init_buttons(){
	GPIOA_MODER &= ~((3 << 7*2) | (3 << 4*2)); // shifts the bits to where 3 ,4 are then clears them

	GPIOA_MODER &= ~(3 << 5*2);  // Clear bits 10 and 11 (led)

	GPIOA_MODER |=  (1 << 5*2);  // Set bit 10 to 1 (01 = Output)

	GPIOA_PUPDR &= ~((3 << 7*2) | (3 << 4*2));  // clearing the bits for the pull up registor

	GPIOA_PUPDR |= ((1 << 7*2) | (1 << 4*2));// pull up reg setting it to 01 for pull up we want the button to be high when not pressed
}

