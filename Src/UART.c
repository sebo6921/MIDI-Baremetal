/*
 * UART.C
 *
 *  Created on: Jun 5, 2026
 *      Author: libak
 */
#include "Registers.h"
#include "ringBuffer.h"
#include "Clock.h"

#define UART3_TX_CAPACITY 64

// 1. Permanently allocate raw bytes in RAM for our encapsulated container
static uint8_t uart3_tx_pool[RING_BUFFER_MEMORY_SIZE(UART3_TX_CAPACITY)];
static ringBuffer_t *uart3_tx_buffer = NULL;

void init_uart()
{
    // 2. Configure PB10 as Alternate Function (AF7 = USART3_TX)
    GPIOB_MODER &= ~(3U << (10 * 2));
    GPIOB_MODER |=  (2U << (10 * 2));      // Mode 2: Alternate Function

    GPIOB_AFRH  &= ~(0xFU << (8));     // clear the bits
    GPIOB_AFRH  |=  (7U << (8));       // AF7

    GPIOB_PUPDR &= ~(3U << (10*2));
    GPIOB_PUPDR |=  (1U << (10*2));       // set PB10 to Pull-up

    // 4. Configure USART3 Parameters
    USART3_BRR = 0x008B;
    USART3_CR1 |= (1U << 13);              // UE: USART Enable
    USART3_CR1 |= (1U << 3);               // TE: Transmitter Enable
    // USART3_CR1 |= (1U << 2);               // RE: Receiver Enable

    // 2. Clear pointer to act as our safe API handle
    uart3_tx_buffer = ringBuffer_create(uart3_tx_pool, UART3_TX_CAPACITY);

}

void uart_send_byte(uint8_t data)
{
	 ringBuffer_push(data, uart3_tx_buffer);


}

void uart_send_string(const char *str) {
	while (!ringBuffer_empty(uart3_tx_buffer))
	{// wait until the transmitting bufer is empty
	}
	__disable_irq();
    while (*str) {
        uart_send_byte((uint8_t)*str);
        str++;
    }
    __enable_irq();
    // 2. Check if the TXEIE (Bit 7) inside USART3_CR1 is currently turned off
    	 	// TXE is Bit 7 in the Status Register (USART2_SR)
    	    if ((USART3_CR1 & (1U << 7)) == 0)
    	    {
    	    	// 3. Flip TXEIE to 1. Because the hardware transmission register is empty,
    			// this instantly wakes up the hardware and fires the USART3_IRQHandler!
    			USART3_CR1 |= (1U << 7);
    	    }
}

void USART3_IRQHandler()
{
	// check if usart3 sr is empty meaning no data in there
	// and  if the interrupt is enabled
	if (USART3_SR & (1U << 7) && USART3_CR1 & (1U << 7))
	{
		uint8_t outdata;
		//if success meaning we popped into outdata we write the value into the dr register
		// wiriting to dr reg the txe bit is cleared
		if (ringBuffer_pop(uart3_tx_buffer, &outdata)){

			USART3_DR = outdata;


	}else{
		// clear the interrupt bit or else it will keep triggering
		 USART3_CR1 &= ~(1U << 7);
	}
	}
}

