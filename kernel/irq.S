.syntax unified
.cpu cortex-m4
.thumb

.global irq_save
.type irq_save, %function

irq_save:
    mrs r0, primask
    cpsid i
    bx lr

.global irq_restore
.type irq_restore, %function

irq_restore:
    msr primask, r0
    bx lr