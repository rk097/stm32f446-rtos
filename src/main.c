#include "stm32f446re.h"
#include "systick.h"

int main(void) {
    SysTick_Init();

    RCC_AHB1ENR |= 1; // enable bit 0 for GPIOA.
    GPIOA_MODER &= ~(0b11 << 10); // clear MODER5
    GPIOA_MODER |= (1 << 10); // output mode for pin A5

    while (1) {
        GPIOA_BSRR = (1UL << 5);  // LED on
        delay_ms(500);
        GPIOA_BSRR = (1UL << 21); // LED off
        delay_ms(500);
    }   
}