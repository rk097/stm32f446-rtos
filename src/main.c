#include "stm32f446re.h"
#include "systick.h"
#include "uart.h"
#include "nucleo.h"
#include "task.h"
#include <stdint.h>

void taskA(void)
{
    while (1) {
        uart_write_str("A\r\n");
        delay_ms(100);
        task_yield();
    }
}

void taskB(void)
{
    while (1) {
        uart_write_str("B\r\n");
        delay_ms(100);
        task_yield();
    }
}

int main(void) {
    LED_Init();
    SysTick_Init();
    USART2_Init();

    uart_write_str("Creating tasks...\r\n\n");

    delay_ms(500);

    task_create(taskA);
    task_create(taskB);

    begin_tasks();

    while(1) {}
}