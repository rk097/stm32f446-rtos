#include "pendsv.h"
#include "cortex_m4.h"

void PendSV_Init(void) {
    SCB_SHPR3 |= (0xF0 << 16);
}