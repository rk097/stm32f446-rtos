#include "uart.h"
#include "nvic.h"
#include "stm32f446re.h"
#include "gpio.h"

#define UART_RX_BUF_SIZE 128

static uint8_t rx_buf[UART_RX_BUF_SIZE];
static volatile uint16_t rx_head;
static volatile uint16_t rx_tail;

void USART2_Init(void) {
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

void uart_write_byte(uint8_t b) {
    while (!(USART2_SR & (1 << 7))) {}
    USART2_DR = b;
}

void uart_write_str(const char* str) {
    while (*str) {
        uart_write_byte(*str++);
    }
}

/**
 * Reads one byte if available, or returns 0 if not.
 * @param b Pointer to uint8_t to store read byte
 * @return 1 if byte was read, 0 if not
 */
int uart_read_byte(uint8_t* b) {
    if (rx_tail == rx_head) return 0;
    *b = rx_buf[rx_tail];
    rx_tail = (rx_tail + 1) % UART_RX_BUF_SIZE;
    return 1;
}

void USART2_IRQ_Handler(void) {
    if (USART2_SR & (1 << 5)) {
        uint8_t c = USART2_DR;
        uint16_t next_head = (rx_head + 1) % UART_RX_BUF_SIZE;
        if (next_head != rx_tail) {
            rx_buf[rx_head] = c;
            rx_head = next_head;
        }
    }
}