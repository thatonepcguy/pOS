#include "common.h"
#include "memory.h"
#include "mmio.h"
#include "uart.h"
#include "string.h"
#include "heap.h"
#include "kprintf.h"

extern char __bss[], __bss_end[];
extern char __heap[], __heap_end[];
extern char __kernel[];
extern char _vector_table[];

void main(void) {
    // init bss
    memset(__bss, 0, (uint64_t)__bss_end - (uint64_t)__bss);
    // zero out heap
    memset(__heap, 0, (uint64_t)__heap_end - (uint64_t)__heap);

    // init the vector table
    sysRegWrite(VBAR_EL1, (uint64_t)_vector_table);

    // init uart
    uartInit();
    txReady();
    kprintf("Kernel Start: 0x%x\r\n", (uint64_t)__kernel);
    kprintf("Heap Start: 0x%x\r\n", (uint64_t)__heap);

    // init and test heap
    initHeap((paddr_t)__heap);
    char *ptr = kalloc(129);
    kprintf("0x%x\r\n", (uint64_t)ptr);

    int c;

    while(1) {
        if ((c = uartGetc()) != -1)
            uartPutc((char)c);
    }
}