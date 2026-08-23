#include "uart.h"
#include "nvic.h"
#include "stm32f446re.h"
#include "gpio.h"

void USART2_Init() {
    GPIOA_Init();
    RCC_APB1ENR |= (1 << 17); // enable USART2 clock
    GPIOA_MODER &= ~(0b11 << 4);
    GPIOA_MODER &= ~(0b11 << 6);
    GPIOA_MODER |= (0b10 << 4);
    GPIOA_MODER |= (0b10 << 6); // pins A2 and A3 for TX and RX resp.
    GPIOA_AFRL &= ~(0b1111 << 8);
    GPIOA_AFRL &= ~(0b1111 << 12);
    GPIOA_AFRL |= (0b111 << 8);
    GPIOA_AFRL |= (0b111 << 12); // enable alt function USART2
    // for baud rate, we use the formula to get 11 for frac and 8 for mantissa
    // 115200bps 8N1
    USART2_BRR = ((0x8 << 4) | 11);
    USART2_CR1 |= (0b11 << 2); // enable tx and rx
    nvic_enable_USART2_IRQ();
    USART2_CR1 |= (1 << 5); // enable RX interrupt
    USART2_CR1 |= (1 << 13); // enable peripheral.
}

void uart_write_char(char c) {
    while (!(USART2_SR & (1 << 7))) {}
    USART2_DR = c;
}

void uart_write(const char* str) {
    while (*str) {
        uart_write_char(*str++);
    }
}

void USART2_IRQ_Handler() {
    if (USART2_SR & (1 << 5)) {
        char c = USART2_DR;
        uart_write("\nReceived: ");
        uart_write_char(c);
    }
}