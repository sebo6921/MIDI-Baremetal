/*
 * UART.C
 *
 *  Created on: Jun 5, 2026
 *      Author: libak
 */
#include "Registers.h"
void init_uart()
{
	RCC_APB1ENR |= (1U<<17);
	GPIOA_MODER &= ~(3 << 2*2);
	GPIOA_MODER |= (2U << 2*2);
	GPIOA_AFRL &= ~(0xF<<2*4);
	GPIOA_AFRL |= (7<<2*4);
	USART2_BRR = 0x16D;
	USART2_CR1 |= (1U<<13);
	USART2_CR1 |= (1U<<3);
}

void uart_send_byte(uint8_t data)
{
	// Wait until the Transmit Data Register Empty (TXE) flag is set
	    // TXE is Bit 7 in the Status Register (USART2_SR)
	    while (!(USART2_SR & (1U << 7)))
	    {
	        // Do nothing until the hardware is ready for the next byte
	    }

	    // Stuff the byte into the mailbox slot
	    USART2_DR = data;
}
