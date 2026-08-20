#ifndef STM32F446RE_H
#define STM32F446RE_H

#include <stdint.h>

#define RCC_BASE 0x40023800UL
#define RCC_AHB1ENR *(volatile uint32_t*)(RCC_BASE + 0x30U)
#define RCC_APB1ENR *(volatile uint32_t*)(RCC_BASE + 0x40U)

#define GPIOA_BASE 0x40020000UL
#define GPIOA_MODER *(volatile uint32_t*)(GPIOA_BASE)
#define GPIOA_BSRR *(volatile uint32_t*)(GPIOA_BASE + 0x18U)
#define GPIOA_AFRL *(volatile uint32_t*)(GPIOA_BASE + 0x20U)

#define USART2_BASE 0x40004400UL
#define USART2_SR *(volatile uint32_t*)(USART2_BASE)
#define USART2_DR *(volatile uint32_t*)(USART2_BASE + 0x4U)
#define USART2_BRR *(volatile uint32_t*)(USART2_BASE + 0x8U)
#define USART2_CR1 *(volatile uint32_t*)(USART2_BASE + 0xCU)

#endif