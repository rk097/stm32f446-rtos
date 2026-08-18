#include "stm32f446re.h"

volatile uint32_t systick_ms = 0;

void SysTick_Handler(void)
{
    systick_ms++;
}

int main(void) {

    SYSTICK_CURRENT = 0;
    SYSTICK_RELOAD = 15999; // 16000 - 1, assuming 16 MHz
    SYSTICK_CTRL_STAT = 0b111;

    RCC_AHB1ENR |= 1; // enable bit 0 for GPIOA.
    GPIOA_MODER &= ~(0b11 << 10); // clear MODER5
    GPIOA_MODER |= (1 << 10); // output mode for pin A5

    while (1) {
        GPIOA_BSRR = (1UL << 5);  // LED on
        
        uint32_t start = systick_ms;
        while ((systick_ms - start) < 1000) {}

        GPIOA_BSRR = (1UL << 21); // LED off

        start = systick_ms;
        while ((systick_ms - start) < 1000) {}
    }   
}