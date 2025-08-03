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

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t paddr_t;
typedef uint64_t vaddr_t;

#define is_aligned(ptr, align) (((uintptr_t)(ptr) & ((align) - 1)) == 0)
#define va_list __builtin_va_list
#define va_start __builtin_va_start
#define va_end __builtin_va_end
#define va_arg __builtin_va_arg

#define sysRegRead(reg)                                                        \
    ({                                                                         \
        unsigned long __tmp;                                                   \
        __asm__ __volatile__("mrs %0, " #reg : "=r"(__tmp));                   \
        __tmp;                                                                 \
    })

#define sysRegWrite(reg, value)                                               \
    do {                                                                      \
        uint64_t __tmp = (value);                                             \
        __asm__ __volatile__("msr " #reg ", %0" ::"r"(__tmp));                \
    } while (0)

#define dmb() __asm__ __volatile__("dmb sy" ::: "memory")
#define dsb() __asm__ __volatile__("dsb sy" ::: "memory")
#define isb() __asm__ __volatile__("isb sy" ::: "memory")

size_t bitscan(size_t x); 
size_t pow2RoundUp(size_t x);
size_t pow(size_t x, size_t power);