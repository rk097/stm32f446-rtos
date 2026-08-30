.syntax unified
.cpu cortex-m4
.thumb

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

.global save_context
.type save_context, %function

save_context:
    mrs r0, psp
    stmdb r0!, {r4-r11}
    bx lr