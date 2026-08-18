#include <stdint.h>

extern int main(void);

/* Linker-script symbols */
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

/* Forward declaration */
void Reset_Handler(void);
extern void SysTick_Handler(void);

/*
 * Top of SRAM for STM32F446RE:
 * RAM starts at 0x20000000
 * RAM size is 128 KB = 0x20000
 * so top of RAM is 0x20020000
 */
#define STACK_TOP 0x20020000U

__attribute__((section(".isr_vector")))
const uint32_t vector_table[] =
{
    STACK_TOP,
    (uint32_t)Reset_Handler,
    [15] = (uint32_t)SysTick_Handler
};

void Reset_Handler(void)
{
    uint32_t* src = &_sidata;
    uint32_t* dst = &_sdata;

    while (dst < &_edata)
    {
        *dst++ = *src++;
    }

    dst = &_sbss;

    while (dst < &_ebss)
    {
        *dst++ = 0;
    }

    main();

    while (1)
    {
    }
}