/*
    * raspix is a custom OS designed to function on the Raspberry Pi 5.
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

