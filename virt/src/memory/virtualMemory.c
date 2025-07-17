#include "memory/virtualMemory.h"
#include "utils/common.h"
#include "utils/memory.h"
#include "memory/memAllocator.h"
#include "utils/kprintf.h"
#include "memory/heap.h"

void mapPage(vaddr_t vAddress, paddr_t pAddress, uint8_t attrIndx) {
    
    if (((vAddress & 0xFFFFFF8000000000)>>39) != 0xFFFFFF8 && ((vAddress & 0xFFFFFF8000000000)>>39) != 0x0)
        kpanic("Invalid Virtual Address");
    
    uint64_t *l2PageTable = (uint64_t *)(sysRegRead(ttbr0_el1) & 0x0000FFFFFFFFFFFE);
    if (((vAddress & 0xFFFFFF8000000000)>>39) == 0xFFFFFF8) 
        l2PageTable = (uint64_t *)(sysRegRead(ttbr1_el1) & 0x0000FFFFFFFFFFFE);

    // get page table indexes
    uint32_t vpn2Index = (vAddress >> 30) & 0x1ff;
    uint32_t vpn1Index = (vAddress >> 21) & 0x1ff;
    uint32_t vpn0Index = (vAddress >> 12) & 0x1ff;

    // second level (table pointed to by ttbr0/ttbr1)
    uint64_t *l1PageTable = (uint64_t *)(l2PageTable[vpn2Index] & PTE_ADDRESS_MASK);
    if (!(l2PageTable[vpn2Index] & PTE_VALID)) { // Create a new PTE
        l1PageTable = (uint64_t *)allocPage(1);
        memset(l1PageTable, 0, 1024*4); 
        l2PageTable[vpn2Index] = PTE_VALID | PTE_TABLEPAGE | ((uint64_t)l1PageTable & PTE_ADDRESS_MASK) | PTE_AF;
        kprintf("L1 Created at: 0x%x\r\n", l2PageTable[vpn2Index] & PTE_ADDRESS_MASK);
    }
    // first level (table pointed to by second level)
    uint64_t *l0PageTable = (uint64_t *)(l1PageTable[vpn1Index] & PTE_ADDRESS_MASK);
    if (!(l1PageTable[vpn1Index] & PTE_VALID)) { // Create a new PTE
        l0PageTable = (uint64_t *)allocPage(1);
        memset(l0PageTable, 0, 1024); 
        l1PageTable[vpn1Index] = ((uint64_t)l0PageTable & PTE_ADDRESS_MASK) | PTE_VALID | PTE_TABLEPAGE | PTE_AF;
        kprintf("L0 Created at: 0x%x\r\n", l1PageTable[vpn1Index] & PTE_ADDRESS_MASK);
    }
    
    l0PageTable[vpn0Index]  = (pAddress & PTE_ADDRESS_MASK) | ((attrIndx & 0x7)<<2) | PTE_VALID | PTE_TABLEPAGE | PTE_AF;
    kprintf("mapped 0x%x to 0x%x\r\n", vAddress, pAddress);
}