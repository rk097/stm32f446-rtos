#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "task.h"
#include <stdint.h>

typedef struct {
    uint8_t available;
    task_t* waiter;
} bin_semaphore_t;

void bin_semaphore_init(bin_semaphore_t* sem, uint8_t init_val);
void bin_semaphore_wait(bin_semaphore_t* sem);
void bin_semaphore_post(bin_semaphore_t* sem);

#endif