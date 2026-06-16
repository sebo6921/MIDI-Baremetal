/*
 * Registers.h
 *
 *  Created on: Jun 3, 2026
 *      Author: libak
 */

#ifndef REGISTERS_HPP_
#define REGISTERS_HPP_
#include <stdint.h>

#define GPIOA_BASE      0x40020000U
#define GPIOB_BASE		0x40020400U
#define GPIOC_BASE		0x40020800U

struct GPIO_TypeDef{
    volatile uint32_t MODER;      // 0x00 Sets pin modes (Input, Output, Alternate Function)
    volatile uint32_t OTYPER;     // 0x04
    volatile uint32_t OSPEEDR;    // 0x08
    volatile uint32_t PUPDR;      // 0x0C Turns internal Pull-up or Pull-down resistors on/off
    volatile uint32_t IDR;        // 0x10 Input Data Register (Reads voltage coming into pins)
    volatile uint32_t ODR;        // 0x14 Output Data Register (Sends voltage out to pins)
    volatile uint32_t BSRR;       // 0x18
    volatile uint32_t LCKR;       // 0x1C
    volatile uint32_t AFRL;       // 0x20
    volatile uint32_t AFRH;       // 0x24
};

#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)


#define RCC_BASE        0x40023800U // this is the power block
#define USART3_BASE		0x40004800U
#define SYSCFG_BASE		0x40013800U //
#define EXTI_BASE 		0x40013C00U
#define NVIC_BASE		0xE000E000U
#define ADC_BASE		0x40012000U

#define RCC_APB1ENR 	  *(volatile uint32_t *) (RCC_BASE + 0x40U)
#define RCC_APB2ENR 	  *(volatile uint32_t *) (RCC_BASE + 0x44U)
#define RCC_AHB1ENR   	  *(volatile uint32_t *) (RCC_BASE + 0x30U)
#define RCC_CFGR 		  *(volatile uint32_t *) (RCC_BASE + 0x08U)
#define RCC_PLLCFGR  	  *(volatile uint32_t *) (RCC_BASE + 0x04U)

//ADC
#define ADC_SQR1 *(volatile uint32_t *) (ADC_BASE+0x2CU)
#define ADC_CR2  *(volatile uint32_t *) (ADC_BASE+0x08)
#define ADC_SR1  *(volatile uint32_t *) (ADC_BASE) // status register
#define ADC_DR1  *(volatile uint32_t *) (ADC_BASE+0x4C) // data register
#define ADC_SQR3 *(volatile uint32_t *) (ADC_BASE+0x34)

// interrupts
#define SYSCFG_EXTICR2  *(volatile uint32_t *) (SYSCFG_BASE + 0x0C)
#define SYSCFG_EXTICR3  *(volatile uint32_t *) (SYSCFG_BASE + 0x10) // this controls bits 8-11 - since we use PB8 we need this
#define EXTI_FTSR  		*(volatile uint32_t *) (EXTI_BASE + 0x0C)
#define EXTI_IMR  		*(volatile uint32_t *) (EXTI_BASE + 0x00)
#define NVIC_ISER0  	*(volatile uint32_t *) (0xE000E100) // exti4 and exti9_5 live in pins 10 and 23.  Interrupt Set-Enable Registers have 0-31 so they both fall in the realm
#define NVIC_ISER1  	*(volatile uint32_t *) (0xE000E104) //uart3 interrupt live in pins 39 iser1 32 - 63

#define EXTI_PR			*(volatile uint32_t *) (EXTI_BASE + 0x14) // pending register we set this to 1 to clear the interrupt
#define UART3_INTERRUPT *(volatile uint32_t *) (0x000000DC) // uart3 vector interrrupt address



//Status Register (Checks if the hardware is busy or empty)
#define USART3_SR  *(volatile uint32_t *) (USART3_BASE + 0x00U)
//Data Register (The mailbox slot where you load characters)
#define USART3_DR  *(volatile uint32_t *) (USART3_BASE + 0x04U)
//Baud Rate Register (Controls transmission speed)
#define USART3_BRR *(volatile uint32_t *) (USART3_BASE + 0x08U)
//Control Register 1 (The main power and pin enable dashboard
#define USART3_CR1 *(volatile uint32_t *) (USART3_BASE + 0x0CU)
//Control Register 2 (Advanced layout options, like stop bits)
#define USART3_CR2 *(volatile uint32_t *) (USART3_BASE + 0x10U)
//Control Register 3 (Advanced system features, like DMA)
#define USART3_CR3 *(volatile uint32_t *) (USART3_BASE + 0x14U)


#endif /* REGISTER_H_ */

