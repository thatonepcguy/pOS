#include "common.h"
#include "memory.h"
#include "mmio.h"
#include "uart.h"
#include "memAllocator.h"
#include "traphandler.h"
#include "string.h"
#include "heap.h"
#include "kprintf.h"
#include "timer.h"
#include "uartLoadScreen.h"
#include "tcr_el1_Config.h"
#include "mair_el1_memTypes.h"

extern char __bss[], __bss_end[];
extern char __heap[], __heap_end[];
extern char __ram[], __ram_end[];
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

    // init heap
    initHeap((paddr_t)__heap);

    // init allocator
    initAllocator((paddr_t)__ram);
    
    // create TTBR0 and TTBR1 Page tables
    uint16_t asid = 0;
    uint64_t ttbr0Page = allocPage(1);
    uint64_t ttbr1Page = allocPage(1);
    sysRegWrite(ttbr0_el1, (ttbr0Page & 0x0000FFFFFFFFFFFE) | (uint64_t)asid<<48); // shut up ik its "not safe"
    sysRegWrite(ttbr1_el1, (ttbr1Page & 0x0000FFFFFFFFFFFE) | (uint64_t)asid<<48);

    // set attr0 and attr1 in mair_el1 for cacheable and non cacheable mem
    sysRegWrite(mair_el1, normalCacheableMem | (nonCacheableMem << 8));

    // set tcr_el1 and sctlr_el1

    
    #ifndef BOOTSCRN
        kprintf("Kernel Start: 0x%x\r\n", (uint64_t)__kernel);
        kprintf("Heap Start: 0x%x\r\n", (uint64_t)__heap);
        kprintf("Ram Start: 0x%x\r\n", (uint64_t)__ram);
    #else 
        displayBootScreen();
    #endif

    int c;

    while(1) {
        if ((c = uartGetc()) != -1)
            kprintf("<%c><%d>\r\n", (char)c, c);
    }
}