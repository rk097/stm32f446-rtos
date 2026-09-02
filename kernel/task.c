#include "task.h"
#include "cortex_m4.h"

void task_exit(void) {}

#define MAX_TASKS 4
#define STACK_SIZE 256

static task_t tasks[MAX_TASKS];
static uint32_t task_stacks[MAX_TASKS][STACK_SIZE] __attribute__((aligned(8)));
static uint8_t num_tasks = 0;
static uint8_t cur_task = 0;

task_t* cur_task_handle = &tasks[0];
task_t* next_task_handle = &tasks[0];

void task_yield(void) {
    cur_task = (cur_task + 1) % num_tasks;
    next_task_handle = &tasks[cur_task];
    SCB_ICSR = (1 << 28);
}

void task_init(task_t* task_handle, uint32_t* stack_handle, void (*task_func)(void)) {
    uint32_t* sp = &stack_handle[STACK_SIZE];

    // initial fake hardware context
    *--sp = 0x01000000; // xPSR with thumb bit
    *--sp = (uint32_t)task_func;
    *--sp = (uint32_t)task_exit;
    *--sp = 0xdeadbeef; // r12
    for (int i = 3; i >= 0; i--) *--sp = 0; // r3...r0

    // fake R11-R4
    for (int i = 11; i >= 4; i--) *--sp = 0;
    task_handle->sp = sp; // points at r4
}

void task_create(void (*task_func)(void)) {
    task_init(&tasks[num_tasks], task_stacks[num_tasks], task_func);
    num_tasks++;
}

void begin_tasks(void) {
    __asm volatile ("svc #0");
}