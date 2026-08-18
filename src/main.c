#include "stm32f446re.h"

int main(void) {

    RCC_AHB1ENR |= 1; // enable bit 0 for GPIOA.

    GPIOA_MODER &= ~(0b11 << 10); // clear MODER5
    GPIOA_MODER |= (1 << 10); // output mode for pin A5

    while (1) {
        GPIOA_BSRR = (1UL << 5);  // LED on

        // dumb loop for "delay."
        for (volatile uint32_t i = 0; i < 1000000; i++)
        {
        }

        GPIOA_BSRR = (1UL << 21); // LED off

        for (volatile uint32_t i = 0; i < 1000000; i++)
        {
        }
    }   
}