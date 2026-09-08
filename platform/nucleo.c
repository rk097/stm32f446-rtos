#include "stm32f446re.h"
#include "nucleo.h"
#include "gpio.h"

static uint8_t led_state = 0;

void LED_Init(void) {
    GPIOA_Init();
    GPIOA_MODER &= ~(0b11 << 10); // clear MODER5
    GPIOA_MODER |= (1 << 10); // output mode for pin A5
}

void led_on(void) {
    led_state = 1;
    GPIOA_BSRR = (1UL << 5);  // LED on
}

void led_off(void) {
    led_state = 0;
    GPIOA_BSRR = (1UL << 21); // LED off
}

void led_toggle(void) {
    if (led_state == 1) led_off();
    else led_on();
}