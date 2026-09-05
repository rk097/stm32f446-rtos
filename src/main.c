#include "stm32f446re.h"
#include "systick.h"
#include "uart.h"
#include "nucleo.h"
#include "task.h"
#include "pendsv.h"
#include <stdint.h>

void int_to_str(int32_t value, char *buf) {
    char tmp[11];
    int i = 0;
    int j = 0;
    uint32_t magnitude;

    if (value < 0) {
        buf[j++] = '-';

        // Avoid overflow for INT32_MIN
        magnitude = (uint32_t)(-(value + 1)) + 1;
    } else {
        magnitude = (uint32_t)value;
    }

    if (magnitude == 0) {
        buf[j++] = '0';
        buf[j] = '\0';
        return;
    }

    while (magnitude > 0) {
        tmp[i++] = '0' + (magnitude % 10);
        magnitude /= 10;
    }

    while (i > 0) {
        buf[j++] = tmp[--i];
    }

    buf[j] = '\0';
}

void taskA(void) {
    int x = 0;
    while (1) {
        x++;
        uart_write_str("A\r\n");
        char num[11];
        int_to_str(x, num);
        uart_write_str(num);
        uart_write_str("\r\n");
        delay_ms(100);
    }
}

void taskB(void) {
    int x = 1000;
    while (1) {
        x++;
        uart_write_str("B\r\n");
        char num[11];
        int_to_str(x, num);
        uart_write_str(num);
        uart_write_str("\r\n");
        delay_ms(100);
    }
}

void taskC(void) {
    int x = 10000;
    while (1) {
        x++;
        uart_write_str("C\r\n");
        char num[11];
        int_to_str(x, num);
        uart_write_str(num);
        uart_write_str("\r\n");
        delay_ms(100);
    }
}

int main(void) {
    LED_Init();
    SysTick_Init();
    USART2_Init();
    PendSV_Init();

    uart_write_str("Creating tasks...\r\n\n");

    delay_ms(500);

    task_create(taskA);
    task_create(taskB);
    task_create(taskC);

    begin_tasks();

    while(1) {}
}