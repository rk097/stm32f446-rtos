#ifndef CORTEX_M4_H
#define CORTEX_M4_H

#include <stdint.h>

#define SYSTICK_BASE 0xE000E010UL
#define SYSTICK_CTRL_STAT *(volatile uint32_t*)(SYSTICK_BASE)
#define SYSTICK_RELOAD *(volatile uint32_t*)(SYSTICK_BASE + 0x4U)
#define SYSTICK_CURRENT *(volatile uint32_t*)(SYSTICK_BASE + 0x8U)

#endif