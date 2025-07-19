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