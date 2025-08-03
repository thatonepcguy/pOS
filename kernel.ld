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

ENTRY(_start)

SECTIONS {
    . = 0x80000;
    .text : ALIGN(4) {
        __kernel = .;
        __text = .;
        KEEP(*(.text.boot));
        *(.text .text.*)
        KEEP(*(.vectors));
        *(.vectors .vectors.*)
        __text_end = .;
    }

    .rodata : ALIGN(4) {
        __rodata = .;
        *(.rodata .rodata.*)
        __rodata_end = .;
    }

    .data : ALIGN(4) {
        __data = .;
        *(.data .data.*)
        __data_end = .;
    }
    
    .bss : ALIGN(4) {
        __bss = .;
        *(.bss .bss.*)
        __bss_end = .;
    }

    .stack : ALIGN(16) {
        __stack = .;
        . += 128 * 1024; /* 128 KiB */ 
        __stack_top = .;
    }

    .heap : ALIGN(128) {
        __heap = .;
        . += 4*1024*1024;
        __heap_end = .;
        __kernel_end = .;
    }

    .ram : ALIGN(4096) {
        __ram = .;
        . += 2*1024*1024*1024;
        __ram_end = .;
    }
}