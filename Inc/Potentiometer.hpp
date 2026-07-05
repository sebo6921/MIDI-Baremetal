/*
 * Potentiometer.hpp
 *
 *  Created on: Jul 2, 2026
 *      Author: libak
 */

#ifndef POTENTIOMETER_HPP_
#define POTENTIOMETER_HPP_

void potention_meter_init(GPIO_TypeDef* gpio,uint8_t pin);
unsigned int read_potentiometer(void);


#endif /* POTENTIOMETER_HPP_ */
