#include "semaphore.h"
#include "task.h"
#include <stddef.h>

extern uint32_t irq_save(void);
extern void irq_restore(uint32_t irq_state);

extern task_t* cur_task_handle;

void bin_semaphore_init(bin_semaphore_t* sem, uint8_t init_val) {
    sem->available = init_val;
    sem->count = 0;
    sem->head = 0;
    sem->tail = 0;
}

void bin_semaphore_wait(bin_semaphore_t* sem) {
    uint32_t irq_state = irq_save();
    if (sem->available == 1) {
        sem->available = 0;
        irq_restore(irq_state);
        return;
    }

    sem->waiters[sem->head] = cur_task_handle;
    sem->head = (sem->head + 1) % MAX_TASKS;
    sem->count++;
    cur_task_handle->state = TASK_BLOCKED;
    irq_restore(irq_state);
    task_schedule_next();
}

void bin_semaphore_post(bin_semaphore_t* sem) {
    uint32_t irq_state = irq_save();
    if (sem->count > 0) { // direct handoff of semaphore to next waiter
        sem->waiters[sem->tail]->state = TASK_READY;
        sem->tail = (sem->tail + 1) % MAX_TASKS;
        sem->count--;
        irq_restore(irq_state);
        return;
    }
    sem->available = 1;
    irq_restore(irq_state);
}