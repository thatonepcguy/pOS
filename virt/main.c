#include "common.h"
#include "memory.h"
#include "mmio.h"
#include "uart.h"
#include "string.h"
#include "kprintf.h"

extern char __bss[], __bss_end[];
extern char _vector_table[];

void main(void) {
    // init bss
    memset(__bss, 0, (uint64_t)__bss_end - (uint64_t)__bss);

    // init the vector table
    sysRegWrite(VBAR_EL1, (uint64_t)_vector_table);

    // init uart
    uartInit();
    txReady();
    kprintf("Hello World!\r\n");

    int c;

    while(1) {
        if ((c = uartGetc()) != -1)
            uartPutc((char)c);
    }
}