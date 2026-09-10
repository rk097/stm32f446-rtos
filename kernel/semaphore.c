#include "semaphore.h"
#include "task.h"
#include <stddef.h>

extern uint32_t irq_save(void);
extern void irq_restore(uint32_t irq_state);

extern task_t* cur_task_handle;

void bin_semaphore_init(bin_semaphore_t* sem, uint8_t init_val) {
    sem->available = init_val;
    sem->waiter = NULL;
}

// does not support multiple waiters
void bin_semaphore_wait(bin_semaphore_t* sem) {
    uint32_t irq_state = irq_save();
    if (sem->available == 1) {
        sem->available = 0;
        irq_restore(irq_state);
        return;
    }
    sem->waiter = cur_task_handle;
    cur_task_handle->state = TASK_BLOCKED;
    irq_restore(irq_state);
    task_schedule_next();
}

void bin_semaphore_post(bin_semaphore_t* sem) {
    uint32_t irq_state = irq_save();
    if (sem->waiter != NULL) {
        sem->waiter->state = TASK_READY;
        sem->waiter = NULL;
        irq_restore(irq_state);
        return;
    }
    sem->available = 1;
    irq_restore(irq_state);
}