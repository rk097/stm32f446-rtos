#include "stm32f446re.h"
#include "systick.h"
#include "uart.h"
#include "nucleo.h"
#include "task.h"
#include "pendsv.h"
#include "semaphore.h"
#include <stdint.h>

static bin_semaphore_t data_ready; // producer to consumer
static bin_semaphore_t buffer_free; // for uart buffer
static volatile uint32_t sample;

extern void int_to_str(int32_t value, char *buf);

void producer_task(void) {
    uint32_t value = 0;

    while (1) {
        bin_semaphore_wait(&buffer_free);

        sample = value++;

        uart_write_str("Producer: sample generated\r\n");

        bin_semaphore_post(&data_ready);

        task_sleep(500);
    }
}

void consumer_task(void) {
    while (1) {
        bin_semaphore_wait(&data_ready);

        uint32_t value = sample;

        char num[11];
        int_to_str(value, num);

        uart_write_str("Consumer: sample processed\r\nValue: ");
        uart_write_str(num);
        uart_write_str("\r\n");

        task_sleep(2000);

        bin_semaphore_post(&buffer_free);
    }
}

void heartbeat_task(void) {
    while (1) {
        led_toggle();
        task_sleep(1000);
    }
}

int main(void) {
    LED_Init();
    SysTick_Init();
    USART2_Init();
    PendSV_Init();
    bin_semaphore_init(&data_ready, 0);   // no sample initially
    bin_semaphore_init(&buffer_free, 1);  // producer may write immediately

    uart_write_str("Creating tasks...\r\n\n");

    delay_ms(500);

    task_create(producer_task);
    task_create(consumer_task);
    task_create(heartbeat_task);

    begin_tasks();

    while(1) {}
}