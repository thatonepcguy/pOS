.extern _current_el_sync_trap
.extern _current_el_int_trap
.extern _current_el_s_trap

.extern _lower_el_sync_trap
.extern _lower_el_int_trap
.extern _lower_el_s_trap

.section ".text.vectors"
.align 11
.global _vector_table
_vector_table:
_current_el_SP0:
    b _current_el_sync_trap
    .rept 31
        nop
    .endr
    b _current_el_int_trap
    .rept 31
        nop
    .endr
    b _current_el_int_trap
    .rept 31
        nop
    .endr
    b _current_el_s_trap
    .rept 31
        nop
    .endr
_current_el_SPx:
    b _current_el_sync_trap
    .rept 31
        nop
    .endr
    b _current_el_int_trap
    .rept 31
        nop
    .endr
    b _current_el_int_trap
    .rept 31
        nop
    .endr
    b _current_el_s_trap
    .rept 31
        nop
    .endr
_lower_el_aarch64:
    b _lower_el_sync_trap
    .rept 31
        nop
    .endr
    b _lower_el_int_trap
    .rept 31
        nop
    .endr
    b _lower_el_int_trap
    .rept 31
        nop
    .endr
    b _lower_el_s_trap
    .rept 31
        nop
    .endr
_lower_el_aarch32:
    b _lower_el_sync_trap
    .rept 31
        nop
    .endr
    b _lower_el_int_trap
    .rept 31
        nop
    .endr
    b _lower_el_int_trap
    .rept 31
        nop
    .endr
    b _lower_el_s_trap
    .rept 31
        nop
    .endr