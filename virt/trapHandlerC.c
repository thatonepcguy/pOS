#include "traphandler.h"
#include "common.h"
#include "kprintf.h"

void handleTrap(trap_t *trapRegs, uint64_t esr_el1) {
    kprintf("Trap Cause: %x\r\n", esr_el1);
    kpanic("");
}