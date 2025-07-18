#include "exceptions/traphandler.h"
#include "utils/common.h"
#include "utils/kprintf.h"

void handleTrap(trap_t *trapRegs, uint64_t esr_el1) {
    switch (esr_el1 & ESR_EL1_EC) {
    case SVC_TRAP:
            __asm__ __volatile__("eret" ::: "memory");
        break;
    
    default:
        kprintf("Trap Cause: %x\r\n", esr_el1);
        while (1);
        break;
    };
}