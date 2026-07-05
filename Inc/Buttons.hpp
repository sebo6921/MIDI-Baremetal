/*
 * Buttons.h
 *
 *  Created on: Jun 3, 2026
 *      Author: libak
 */

#ifndef BUTTONS_HPP_
#define BUTTONS_HPP_
#include <stdint.h>
#include "Registers.hpp"

void init_clock();
void init_buttons(GPIO_TypeDef* gpio,uint8_t pin);
void init_on_board_led(GPIO_TypeDef* gpio,uint8_t pin);
#endif /* BUTTONS_HPP_ */
