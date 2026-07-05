/*
 * PotentioMeter.c
 *
 *  Created on: Jun 10, 2026
 *      Author: libak
 */
#include <Registers.hpp>
#include "Delay.h"

void potention_meter_init(GPIO_TypeDef* gpio,uint8_t pin)
{
	gpio->MODER &= ~((3<<pin*2)); // clear and shift the bits PA1 since we clear we make them 00 which is teh same as input mode
	gpio->MODER |= (3<<pin*2);
	gpio->PUPDR &= ~(3 << pin*2); // make the bits 11 which is analog input

	RCC_APB2ENR |= (1<<8); // turn on the adc1  bit 8

	ADC_SQR3 = 1; // assign pa1 to the adc register
	ADC_CR2 |= (1U<<0); // enable the adc
	ADC_CR2 |= (1U<<1); // continous conversation

	delay_cycles(10000);
	ADC_CR2 |= (1U<<30); // start the injestion
}

unsigned int read_potentiometer(void)
{
    // We loop and do nothing until Bit 1 (EOC) of the status register turns into a 1.
	// gets cleared by software or by reading the ADC_DR1
    while (!(ADC_SR1 & (1 << 1)))
    {
        // Waiting for the hardware to finish the current sample
    }

    // Once it's ready, we grab the value out of the data register
    return ADC_DR1;
}
