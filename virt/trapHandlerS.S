.section ".rodata"
intPanicStr:
    .asciz "Interrupt"
sPanicStr:
    .asciz "Hardware Issue"

.section ".text.vectors.handler"
.global _current_el_sync_trap
.global _lower_el_sync_trap

.global _current_el_int_trap
.global _lower_el_int_trap

.global _lower_el_s_trap
.global _current_el_s_trap

.extern kpanic
.extern handleTrap

_current_el_sync_trap:
_lower_el_sync_trap:
    stp X0, X1,     [SP, #-16]!
    stp X2, X3,     [SP, #-16]!
    stp X4, X5,     [SP, #-16]!
    stp X6, X7,     [SP, #-16]!
    stp X8, X9,     [SP, #-16]!
    stp X10, X11,   [SP, #-16]!
    stp X12, X13,   [SP, #-16]!
    stp X14, X15,   [SP, #-16]!
    stp X16, X17,   [SP, #-16]!
    stp X18, X19,   [SP, #-16]!
    stp X20, X21,   [SP, #-16]!
    stp X22, X23,   [SP, #-16]!
    stp X24, X25,   [SP, #-16]!
    stp X26, X27,   [SP, #-16]!
    stp X28, X29,   [SP, #-16]!
    str X30,        [SP, #-16]!
    mov X0, SP // make registers into a struct * arg
    mrs X1, esr_el1
    bl handleTrap
    ldr X30, [SP], #16
    ldp X28, X29,   [SP], #16
    ldp X26, X27,   [SP], #16
    ldp X24, X25,   [SP], #16
    ldp X22, X23,   [SP], #16
    ldp X20, X21,   [SP], #16
    ldp X18, X19,   [SP], #16
    ldp X16, X17,   [SP], #16
    ldp X14, X15,   [SP], #16
    ldp X12, X13,   [SP], #16
    ldp X10, X11,   [SP], #16
    ldp X8, X9,     [SP], #16
    ldp X6, X7,     [SP], #16
    ldp X4, X5,     [SP], #16
    ldp X2, X3,     [SP], #16
    ldp X0, X1,     [SP], #16
    eret

_current_el_int_trap:
_lower_el_int_trap:
    ldr X0, =intPanicStr
    bl kpanic
    b .

_lower_el_s_trap:
_current_el_s_trap:
    ldr X0, =sPanicStr
    bl kpanic
    b .