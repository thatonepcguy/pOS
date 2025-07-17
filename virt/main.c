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
#include "tcr_el1_config.h"
#include "sctlr_el1_config.h"
#include "mair_el1_config.h"
#include "virtualMemory.h"

extern char __bss[], __bss_end[];
extern char __heap[], __heap_end[];
extern char __ram[], __ram_end[];
extern char __kernel[], __kernel_end[];
extern char _vector_table[];

void main(void) {
    // turn off i and d caches (for boot)
    sysRegWrite(sctlr_el1, sysRegRead(sctlr_el1) & ~(SCTLR_EL1_I | SCTLR_EL1_C));

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
    memset((uint64_t *)ttbr0Page, 0, PAGE_SIZE);
    memset((uint64_t *)ttbr1Page, 0, PAGE_SIZE);
    sysRegWrite(ttbr0_el1, (ttbr0Page & 0x0000FFFFFFFFFFFE) | (uint64_t)asid<<48); // ttbr0 (lower half) of addresses is kernel space
    sysRegWrite(ttbr1_el1, (ttbr1Page & 0x0000FFFFFFFFFFFE) | (uint64_t)asid<<48);

    kprintf("0x%x\r\n", sysRegRead(ttbr0_el1));
    // set attr0 and attr1 in mair_el1 for cacheable and mmio mem
    sysRegWrite(mair_el1, normalCacheableMem | (nGnRnEMem << 8));

    // set tcr_el1
    sysRegWrite(tcr_el1, (IPS_SIZE | TG1 | SH1 | ORGN1 | IRGN1 | 
                          T1SZ | TG0 | SH0 | ORGN0 | IRGN0 | T0SZ) | 
                         (TCR_EL1_E0PD0 | TCR_EL1_A1)); // ttbr1 (user space ttbr) defines the asid
    
    // setup page tables   
    for (uint64_t i = (uint64_t)__kernel; i < (uint64_t)__kernel_end; i += PAGE_SIZE) {
        mapPage(i, i, 0);
    }
    mapPage(UART0_BASE, UART0_BASE, 1);
    
    
    __asm__ __volatile__("tlbi vmalle1\n"
                         "dsb ish\n"
                         "isb\n" ::: "memory");

    // enable mmu
    sysRegWrite(sctlr_el1, (SCTLR_EL1_TWEDEL | SCTLR_EL1_TCF | SCTLR_EL1_TCF0) | 
                           (SCTLR_EL1_TIDCP | SCTLR_EL1_NMI | SCTLR_EL1_ATA | SCTLR_EL1_TCF | SCTLR_EL1_TCF0 | 
                            SCTLR_EL1_ITFSB | SCTLR_EL1_EIS | SCTLR_EL1_EOS | SCTLR_EL1_I | SCTLR_EL1_SA | SCTLR_EL1_SA0 |
                            SCTLR_EL1_C | SCTLR_EL1_M));

    __asm__ __volatile__("dsb ish\n"
                         "isb\n" ::: "memory");
    
    // bootscreen
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