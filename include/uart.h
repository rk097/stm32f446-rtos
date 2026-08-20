#ifndef UART_H
#define UART_H

void USART2_Init();
void uart_write_char(char c);
void uart_write(const char* str);

#endif