.syntax unified
.cpu cortex-m4
.thumb

.global start_task
.type start_task, %function

start_task:
    ldmia r0!, {r4-r11} /* r0 holds sp as the first arg */
    ldr r1, [r0], #4 /* LR is the first reg below sp originally */

    msr psp, r0

    movs r2, #2
    msr CONTROL, r2
    isb

    bx r1
