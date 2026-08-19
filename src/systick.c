#include "cortex_m4.h"
#include "systick.h"

volatile uint32_t systick_ms = 0;

void SysTick_Init(void) {
    SYSTICK_CURRENT = 0;
    SYSTICK_RELOAD = 15999; // 16000 - 1, assuming 16 MHz
    SYSTICK_CTRL_STAT = 0b111;
}

void SysTick_Handler(void)
{
    systick_ms++;
}

void delay_ms(uint32_t delay_length_ms) {
    uint32_t start = systick_ms;
    while ((systick_ms - start) < delay_length_ms) {}
}