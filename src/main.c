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

    // Let both consumers block on data_ready first.
    task_sleep(500);

    while (1) {
        bin_semaphore_wait(&buffer_free);

        sample = value++;

        uart_write_str("Producer: generated ");

        char num[11];
        int_to_str(sample, num);
        uart_write_str(num);
        uart_write_str("\r\n");

        bin_semaphore_post(&data_ready);

        task_sleep(250);
    }
}

static void consumer(const char *name) {
    while (1) {
        bin_semaphore_wait(&data_ready);

        uint32_t value = sample;

        // Free the shared sample slot once we've copied it locally.
        bin_semaphore_post(&buffer_free);

        char num[11];
        int_to_str(value, num);

        uart_write_str("Consumer ");
        uart_write_str(name);
        uart_write_str(": processed ");
        uart_write_str(num);
        uart_write_str("\r\n");

        task_sleep(1000);
    }
}

void consumer_a_task(void) {
    consumer("A");
}

void consumer_b_task(void) {
    consumer("B");
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
    task_create(consumer_a_task);
    task_create(consumer_b_task);
    task_create(heartbeat_task);

    begin_tasks();

    while(1) {}
}