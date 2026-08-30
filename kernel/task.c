#include "task.h"

extern void start_task(uint32_t* sp);
extern void context_switch(uint32_t** old_sp, uint32_t* new_sp);

#define MAX_TASKS 4
#define STACK_SIZE 256

static task_t tasks[MAX_TASKS];
static uint32_t task_stacks[MAX_TASKS][STACK_SIZE] __attribute__((aligned(8)));
static uint8_t num_tasks = 0;
static uint8_t cur_task = 0;

void task_yield(void) {
    uint8_t old_task = cur_task;
    cur_task = (old_task + 1) % num_tasks;
    context_switch(&tasks[old_task].sp, tasks[cur_task].sp);
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
    start_task(tasks[cur_task].sp);
}