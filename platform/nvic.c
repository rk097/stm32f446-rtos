#include "nvic.h"
#include "cortex_m4.h"

void nvic_enable_USART2_IRQ(void) {
    NVIC_ISER1 |= (1 << 6);
}