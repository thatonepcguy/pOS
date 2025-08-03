/*
    * raspix is a custom OS designed to function on the Raspberry Pi 4b.
    * Copyright (C) 2025  Caleb A. Jacka
    *  
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    * 
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <https://www.gnu.org/licenses/>.
    * 
    * If contact with the original author is needed, he is available via email at 
    * calebjacka@gmail.com
*/

.extern __stack_top
.extern main

.section ".text.boot"
.global _start

_start:
    mrs x0, mpidr_el1
    and x0, x0, #0xFF
    cbnz x0, halt

_init:
    movz x0, #0
    msr sctlr_el1, x0

    ldr x0,=0x80000000
    msr hcr_el2, x0

    movz x0, #0x3c5
    msr spsr_el2,x0

    ldr x0, =main
    msr elr_el2, x0

    ldr x0, =__stack_top
    msr sp_el1, x0

    eret

halt:
    wfe
    b halt
    