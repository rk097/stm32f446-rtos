.syntax unified
.cpu cortex-m4
.thumb

.global PendSV_Handler
.type PendSV_Handler, %function

PendSV_Handler:
    mrs r0, psp
    stmdb r0!, {r4-r11}
    ldr r1, =cur_task_handle
    ldr r2, [r1]
    str r0, [r2]

    ldr r0, =next_task_handle
    ldr r0, [r0]
    ldr r2, [r0]
    ldmia r2!, {r4-r11}
    msr psp, r2

    str r0, [r1] /* update cur_task_handle to next_task_handle */

    bx lr

.global SVC_Handler
.type SVC_Handler, %function

SVC_Handler:
    ldr   r0, =cur_task_handle
    ldr   r0, [r0]          /* r0 = cur_task_handle */
    ldr   r0, [r0]          /* r0 = cur_task_handle->sp */

    ldmia r0!, {r4-r11}
    msr   psp, r0

    ldr   lr, =0xFFFFFFFD    /* return to Thread mode using PSP */
    bx    lr