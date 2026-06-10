/*
 * Interrupt.h
 *
 *  Created on: Jun 4, 2026
 *      Author: libak
 */

#ifndef INTERRUPTBUTTONS_H_
#define INTERRUPTBUTTONS_H_
void init_interrupt_buttons();
void init_interrupt();
void EXTI4_IRQHandler();
void EXTI9_5_IRQHandler();
void init_interrupt_clocks();
void init_interrupt_vector_table_bit();

#endif /* INTERRUPTBUTTONS_H_ */
