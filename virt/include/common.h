#pragma once
// c standard library stuff
typedef int bool;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

typedef uint32_t size_t;
typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;

#define true 1;
#define false 0;
#define NULL ((void *) 0)
#define align_up(value, align) __builtin_align_up(value, align)
#define is_aligned(value, align) __builtin_is_aligned(value, align)
#define offsetof (type, member) __builtin_offsetof(type, member)
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