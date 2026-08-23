#include "stm32f446re.h"
#include "systick.h"
#include "uart.h"
#include "nucleo.h"
#include <stdint.h>

int main(void) {
    LED_Init();
    SysTick_Init();
    USART2_Init();

    uint8_t b;
    while (1) {
        if (uart_read_byte(&b)) {
            uart_write_str("\r\nReceived: ");
            uart_write_byte(b);
        }
    }   
}