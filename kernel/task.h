#ifndef TASK_H
#define TASK_H

#include <stdint.h>

typedef struct {
    uint32_t* sp;
} task_t;

void task_create(void (*task_func)(void));
void task_init(task_t* task_handle, uint32_t* stack_handle, void (*task_func)(void));
void task_yield(void);

void begin_tasks(void);

#endif