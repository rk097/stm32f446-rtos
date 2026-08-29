#include "stm32f446re.h"
#include "systick.h"
#include "uart.h"
#include "nucleo.h"
#include "task.h"
#include <stdint.h>

void taskA(void) {
    while (1) {
        uart_write_str("Hello from task A\r\n");
        led_on();
        delay_ms(500);
        task_yield();
    }
}

void taskB(void) {
    while (1) {
        uart_write_str("Hello from task B\r\n");
        led_off();
        delay_ms(500);
        task_yield();
    }
}

int main(void) {
    LED_Init();
    SysTick_Init();
    USART2_Init();

    task_create(taskA);
    task_create(taskB);
    while(1) {}
}