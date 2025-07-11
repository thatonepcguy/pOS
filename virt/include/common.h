#pragma once
// c standard library stuff
typedef unsigned char bool;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
typedef unsigned long uintptr_t;

typedef uint64_t size_t;
typedef uint64_t paddr_t;
typedef uint64_t vaddr_t;

#define true 1;
#define false 0;
#define NULL ((void *) 0)
//#define align_up(value, align) __builtin_align_up(value, align) // may not work
#define is_aligned(ptr, align) (((uintptr_t)(ptr) & ((align) - 1)) == 0)
//#define offsetof (type, member) __builtin_offsetof(type, member) // may not work
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

#define dmb() __asm__ __volatile__("dmb sy")
#define dsb() __asm__ __volatile__("dsb sy")
#define isb() __asm__ __volatile__("isb")

size_t bitscan(size_t x);
size_t pow2RoundUp(size_t x);
size_t pow(size_t x, size_t power);