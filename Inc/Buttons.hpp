/*
 * Buttons.h
 *
 *  Created on: Jun 3, 2026
 *      Author: libak
 */

#ifndef BUTTONS_HPP_
#define BUTTONS_HPP_

void init_clock();
void init_buttons(GPIO_TypeDef* gpio,uint8_t pin);
int read_potentiometer();
void potention_meter_init();
init_on_board_led();
#endif /* BUTTONS_HPP_ */
