/*
    * raspOS is a custom OS designed to function on the Raspberry Pi 5.
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