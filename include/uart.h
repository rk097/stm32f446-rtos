#ifndef UART_H
#define UART_H

#include <stdint.h>

void USART2_Init();
void uart_write_byte(uint8_t b);
void uart_write_str(const char* str);
int uart_read_byte(uint8_t* b);
void USART2_IRQ_Handler();

#endif