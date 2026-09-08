#ifndef TASK_H
#define TASK_H

#include <stdint.h>

// no running, current task is implicitly running
// sleeping distinguished from blocked on semaphore
typedef enum {
    TASK_READY,
    TASK_SLEEPING,
    TASK_BLOCKED
} task_state_t;

// asm assumes sp is at pos 0
typedef struct {
    uint32_t* sp;
    task_state_t state;
    uint32_t wake_tick;
} task_t;

void task_create(void (*task_func)(void));
void task_init(task_t* task_handle, uint32_t* stack_handle, void (*task_func)(void));
void task_schedule_next(void);
void task_sleep(uint32_t ms);

void begin_tasks(void);

#endif