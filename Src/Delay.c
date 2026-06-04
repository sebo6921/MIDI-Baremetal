/*
 * Delay.c
 *
 *  Created on: Jun 4, 2026
 *      Author: libak
 */
#include <stdint.h>
void delay_cycles(uint32_t cycles) {
    while(cycles--) {
        __asm("nop"); // Waste exactly one CPU cycle per loop iteration
    }
}
