#ifndef STM32F446RE_H
#define STM32F446RE_H

#include <stdint.h>

#define RCC_BASE 0x40023800UL
#define RCC_AHB1ENR *(volatile uint32_t*)(RCC_BASE + 0x30U)

#define GPIOA_BASE 0x40020000UL
#define GPIOA_MODER *(volatile uint32_t*)(GPIOA_BASE)
#define GPIOA_BSRR *(volatile uint32_t*)(GPIOA_BASE + 0x18U)

#endif