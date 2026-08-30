#include "task.h"

extern void start_task(uint32_t* sp);
extern uint32_t *save_context(void);

#define MAX_TASKS 4
#define STACK_SIZE 256

static task_t tasks[MAX_TASKS];
static uint32_t task_stacks[MAX_TASKS][STACK_SIZE] __attribute__((aligned(8)));
static uint8_t num_tasks = 0;

void task_yield(void) {
    tasks[0].sp = save_context();
}

void task_init(task_t* task_handle, uint32_t* stack_handle, void (*task_func)(void)) {
    uint32_t* sp = &stack_handle[STACK_SIZE];
    *--sp = (uint32_t)task_func;
    // fake R11-R4
    for (int i = 11; i >= 4; i--) *--sp = 0;
    task_handle->sp = sp; // points at r4
}

void task_create(void (*task_func)(void)) {
    task_init(&tasks[num_tasks], task_stacks[num_tasks], task_func);
    num_tasks++;
}

void begin_tasks(void) {
    start_task(tasks[0].sp);
}