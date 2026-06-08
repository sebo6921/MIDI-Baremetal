/*
 * UART.C
 *
 *  Created on: Jun 5, 2026
 *      Author: libak
 */
#include "Registers.h"
#include "ringBuffer.h"

void init_uart()
{
    // 1. Enable Clocks for GPIOB, GPIOC, and USART3
    RCC_AHB1ENR |= (1U << 1) | (1U << 2); // Enable GPIOB (bit 1) and GPIOC (bit 2)
    RCC_APB1ENR |= (1U << 18);            // Enable USART3 (bit 18)

    // 2. Configure PB10 as Alternate Function (AF7 = USART3_TX)
    GPIOB_MODER &= ~(3U << (10 * 2));
    GPIOB_MODER |=  (2U << (10 * 2));      // Mode 2: Alternate Function

    GPIOB_AFRH  &= ~(0xFU << (2 * 4));     // Pin 10 is index 2 in AFRH (10 - 8 = 2)
    GPIOB_AFRH  |=  (7U << (2 * 4));       // AF7

    // 3. Configure PC5 as Alternate Function with Pull-Up (AF7 = USART3_RX)
    GPIOC_MODER &= ~(3U << (5 * 2));
    GPIOC_MODER |=  (2U << (5 * 2));       // Mode 2: Alternate Function

    GPIOC_AFRL  &= ~(0xFU << (5 * 4));     // Pin 5 is index 5 in AFRL
    GPIOC_AFRL  |=  (7U << (5 * 4));       // AF7

    GPIOC_PUPDR &= ~(3U << (5 * 2));
    GPIOC_PUPDR |=  (1U << (5 * 2));       // Pull-up active

    // 4. Configure USART3 Parameters
    USART3_BRR = 0x683;                    // Baud rate configuration
    USART3_CR1 |= (1U << 13);              // UE: USART Enable
    USART3_CR1 |= (1U << 3);               // TE: Transmitter Enable
    USART3_CR1 |= (1U << 2);               // RE: Receiver Enable
}

void uart_send_byte(uint8_t data)
{
	// Wait until the Transmit Data Register Empty (TXE) flag is set
	    // TXE is Bit 7 in the Status Register (USART2_SR)
	    while (!(USART3_SR & (1U << 7)))
	    {
	        // Do nothing until the hardware is ready for the next byte
	    }

	    // Stuff the byte into the mailbox slot
	    USART3_DR = data;
}
