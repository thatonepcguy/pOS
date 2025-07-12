#include "common.h"
#include "uart.h"
#include "kprintf.h"

void kprintf(const char *fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);

    while(*fmt) {
        if (*fmt == '%') {
            fmt++; // skip % and read character after
            switch (*fmt) {// read next character
                case '\0': // end of format string
                    uartPutc('%');
                    goto end;
                
                case '%':
                    uartPutc('%');
                    break;
                    
                case 's': {// string
                    const char *s = va_arg(vargs, const char *);
                    while (*s) {
                        uartPutc(*s);
                        s++;
                    }
                    break;
                }

                case 'c': {// char
                    const char c = va_arg(vargs, int);
                    uartPutc(c);
                    break;
                }
                
                case 'd': {// integer in decimal
                    int value = va_arg(vargs, int);
                    unsigned magnitude = value;
                    if (value < 0) {
                        uartPutc('-');
                        magnitude = -magnitude;
                    }
                    
                    unsigned divisor = 1;
                    while (magnitude / divisor > 9) {
                        divisor *= 10;
                    }

                    while (divisor > 0) {
                        uartPutc('0' + magnitude/divisor);
                        magnitude %= divisor;
                        divisor /= 10;
                    }
                    break;
                }

                case 'x': {
                    uint64_t value = va_arg(vargs, unsigned);
                    for (int i = 16; i >= 0; i--) {
                        uint64_t nibble = (value >> (i*4)) & 0xf;
                        uartPutc("0123456789abcdef"[nibble]);
                    }
                    break;
                }
                default: {
                    uartPutc(*fmt);
                }
                    
            }
        } else {
            uartPutc(*fmt);
        }

        fmt++;
    }

    end: 
        va_end(vargs);
}

void kpanic(const char *msg) {
        kprintf("panic: %s", msg);
        while (1) {}
}