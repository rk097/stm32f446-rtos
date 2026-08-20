#include "gpio.h"
#include "stm32f446re.h"

void GPIOA_Init() {
    RCC_AHB1ENR |= 1; // enable GPIOA clock
}