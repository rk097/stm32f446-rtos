#include "uart.h"
#include "stm32f446re.h"

void uart_write_char(char c) {
    while (!(USART2_SR & (1 << 7))) {}
    USART2_DR = c;
}

void uart_write(const char* str) {
    while (*str) {
        uart_write_char(*str++);
    }
}