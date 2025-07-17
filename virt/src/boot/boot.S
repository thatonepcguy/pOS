.extern __stack_top
.extern main

.section ".text.boot"
.global _start
_start:
    mrs x10, CurrentEL
    // Park non-main cores
    mrs x11, mpidr_el1
    and x11, x11, #3
    cbnz x11, _hlt

_k_start:
    // init the stack
    ldr x10, =__stack_top
    mov sp, x10
    bl main
    b _hlt

_hlt:
    b _hlt

