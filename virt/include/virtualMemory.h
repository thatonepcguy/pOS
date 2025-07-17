#pragma once
#include "common.h"

#define PTE_VALID       (1ULL<<0)
#define PTE_TABLEPAGE   (1ULL<<1)
#define PTE_AF          (1ULL<<10)

#define PTE_ADDRESS_MASK 0x000000FFFFFFF000

void mapPage(vaddr_t vAddress, paddr_t pAddress, uint8_t attrIndx);