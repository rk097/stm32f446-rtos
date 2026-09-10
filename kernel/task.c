#include "task.h"
#include "config.h"
#include "cortex_m4.h"

#define STACK_SIZE 256

static task_t tasks[MAX_TASKS+1];
static uint32_t task_stacks[MAX_TASKS+1][STACK_SIZE] __attribute__((aligned(8)));
static uint8_t num_tasks = 0;
static uint8_t cur_task = 0;
static uint8_t scheduler_running = 0;

// need to be split so that interrupt can save and restore context for each task
task_t* cur_task_handle = &tasks[0];
task_t* next_task_handle = &tasks[0];

extern volatile uint32_t systick_ms;

// secret extra task if all tasks are blocked. does not contribute to num_tasks but is stored in tasks[]
void idle_task(void) {
    while (1) {
        __asm volatile ("wfi");
    }
}

void task_schedule_next(void) {
    if (scheduler_running) {
        int num_runnable = 0;

        // wake any sleeped tasks that are ready
        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].state == TASK_SLEEPING && (int32_t)(systick_ms - tasks[i].wake_tick) >= 0) tasks[i].state = TASK_READY;
            if (tasks[i].state == TASK_READY) num_runnable++;
        }

        int old_task = cur_task;

        if (num_runnable == 0) {
            cur_task = num_tasks; // idle task is always last
            next_task_handle = &tasks[cur_task];
        } else {
            // if cur task is idle task, check all other tasks
            int start = (cur_task == num_tasks) ? -1 : cur_task;

            for (int i = 1; i <= num_tasks; i++) {
                int candidate = (start + i) % num_tasks;

                if (tasks[candidate].state == TASK_READY) {
                    cur_task = candidate;
                    next_task_handle = &tasks[cur_task];
                    break;
                }
            }
        }
        // switch if there is a new task to switch 
        if (old_task != cur_task) SCB_ICSR = (1 << 28);
    }
}

// sleep current task.
void task_sleep(uint32_t ms) {
    tasks[cur_task].state = TASK_SLEEPING;
    tasks[cur_task].wake_tick = systick_ms + ms;
    task_schedule_next();
}

void task_init(task_t* task_handle, uint32_t* stack_handle, void (*task_func)(void)) {
    uint32_t* sp = &stack_handle[STACK_SIZE];

    // initial fake hardware context
    *--sp = 0x01000000; // xPSR with thumb bit
    *--sp = (uint32_t)task_func;
    *--sp = (uint32_t)idle_task;
    *--sp = 0xdeadbeef; // r12
    for (int i = 3; i >= 0; i--) *--sp = 0; // r3...r0

    // fake R11-R4
    for (int i = 11; i >= 4; i--) *--sp = 0;
    task_handle->sp = sp; // points at r4

    task_handle->state = TASK_READY;
    task_handle->wake_tick = 0;
}

void task_create(void (*task_func)(void)) {
    task_init(&tasks[num_tasks], task_stacks[num_tasks], task_func);
    num_tasks++;
}

void begin_tasks(void) {
    scheduler_running = 1;
    task_init(&tasks[num_tasks], task_stacks[num_tasks], idle_task);
    __asm volatile ("svc #0");
}