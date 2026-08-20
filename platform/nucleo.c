#include "stm32f446re.h"
#include "nucleo.h"
#include "gpio.h"

void LED_Init() {
    GPIOA_Init();
    GPIOA_MODER &= ~(0b11 << 10); // clear MODER5
    GPIOA_MODER |= (1 << 10); // output mode for pin A5
}

void led_on() {
    GPIOA_BSRR = (1UL << 5);  // LED on
}

void led_off() {
    GPIOA_BSRR = (1UL << 21); // LED off
}