.syntax unified
.cpu cortex-m4
.thumb

.global context_switch
.type context_switch, %function

context_switch:
    mrs r2, psp
    str lr, [r2, #-4]!
    stmdb r2!, {r4-r11}
    str r2, [r0]

    ldmia r1!, {r4-r11}
    ldr lr, [r1], #4
    msr psp, r1

    bx lr

.global start_task
.type start_task, %function

start_task:
    ldmia r0!, {r4-r11} /* r0 holds sp as the first arg */
    ldr r1, [r0], #4 /* Load task entry which we stored at stack top */

    msr psp, r0

    movs r2, #2
    msr CONTROL, r2
    isb

    bx r1