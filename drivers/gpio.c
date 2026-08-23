#include "gpio.h"
#include "stm32f446re.h"

void GPIOA_Init(void) {
    RCC_AHB1ENR |= 1; // enable GPIOA clock
}