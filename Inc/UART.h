/*
 * UART.h
 *
 *  Created on: Jun 5, 2026
 *      Author: libak
 */

#ifndef UART_H_
#define UART_H_

void init_uart();
void uart_send_byte(uint8_t data);
void USART3_IRQHandler();
void uart_send_string(const char *str);
#endif /* UART_H_ */
