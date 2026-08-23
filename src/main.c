#include "stm32f446re.h"
#include "systick.h"
#include "uart.h"
#include "nucleo.h"

int main(void) {
    LED_Init();
    SysTick_Init();
    USART2_Init();

    while (1) {
        led_on();
        delay_ms(500);
        led_off();
        delay_ms(500);
    }   
}