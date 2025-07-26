/*
    * raspOS is a custom OS designed to function on the Raspberry Pi 5.
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
    }
    // first level (table pointed to by second level)
    uint64_t *l0PageTable = (uint64_t *)(l1PageTable[vpn1Index] & PTE_ADDRESS_MASK);
    if (!(l1PageTable[vpn1Index] & PTE_VALID)) { // Create a new PTE
        l0PageTable = (uint64_t *)allocPage(1);
        memset(l0PageTable, 0, 1024); 
        l1PageTable[vpn1Index] = ((uint64_t)l0PageTable & PTE_ADDRESS_MASK) | PTE_VALID | PTE_TABLEPAGE | PTE_AF;
    }
    
    l0PageTable[vpn0Index]  = (pAddress & PTE_ADDRESS_MASK) | ((attrIndx & 0x7)<<2) | PTE_VALID | PTE_TABLEPAGE | PTE_AF;
}

void demapPage(vaddr_t vAddress) {
    if (!is_aligned(vAddress, PAGE_SIZE)) {
        kpanic("Unaligned Virtual Address When Demapping Page");
    }

    // EXTRACT THE PAGE TABLE INDEXES FROM THE VIRTUAL ADDRESSES
    if (((vAddress & 0xFFFFFF8000000000)>>39) != 0xFFFFFF8 && ((vAddress & 0xFFFFFF8000000000)>>39) != 0x0)
        kpanic("Invalid Virtual Address");
    
    uint64_t *l2PageTable = (uint64_t *)(sysRegRead(ttbr0_el1) & 0x0000FFFFFFFFFFFE);
    if (((vAddress & 0xFFFFFF8000000000)>>39) == 0xFFFFFF8) 
        l2PageTable = (uint64_t *)(sysRegRead(ttbr1_el1) & 0x0000FFFFFFFFFFFE);

    // get page table indexes
    uint32_t vpn2Index = (vAddress >> 30) & 0x1ff;
    uint32_t vpn1Index = (vAddress >> 21) & 0x1ff;
    uint32_t vpn0Index = (vAddress >> 12) & 0x1ff;

    uint64_t *l1PageTable = (uint64_t *)(l2PageTable[vpn2Index] & PTE_ADDRESS_MASK);
    uint64_t *l0PageTable = (uint64_t *)(l1PageTable[vpn1Index] & PTE_ADDRESS_MASK);
    l0PageTable[vpn0Index] = 0; // Clear Flags

    bool freeTable0 = true;
    for (uint64_t i = 0; i < 512; i++) {
        if (l0PageTable[i] & PTE_VALID) {
            freeTable0 = false;
            break;
        }
    }

    if (freeTable0) {
        l1PageTable[vpn1Index] = 0;
        deallocPage((paddr_t)l0PageTable);
    }

    bool freeTable1 = true;
    for (uint64_t i = 0; i < 512; i++) {
        if (l1PageTable[i] & PTE_VALID) {
            freeTable1 = false;
            break;
        }
    }

    if (freeTable1) {
        l2PageTable[vpn2Index] = 0;
        deallocPage((paddr_t)l1PageTable);
    }
}