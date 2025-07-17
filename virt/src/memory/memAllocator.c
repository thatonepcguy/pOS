#include "utils/memory.h"
#include "utils/kprintf.h"
#include "utils/string.h"
#include "utils/common.h"
#include "memory/heap.h"
#include "memory/memAllocator.h"

static uint8_t *allocatorNodes;
static paddr_t allocatorRamBegin;

static inline uint32_t levelOffset(uint32_t x) {
    return (1U << x) -1;
}

void initAllocator(paddr_t __ram_start) {
    allocatorNodes = kalloc(MEM_BITMAP_LENGTH);
    memset(allocatorNodes, 0, MEM_BITMAP_LENGTH);
    
    allocatorNodes[0] |= ALLOCATOR_NODE_VALID;
    allocatorRamBegin = __ram_start;
}

paddr_t allocPage(size_t pages) {
    if (pages > MEM_MAX_ALLOCATE_SIZE || pages == 0) {
        kpanic("Invalid Amount of Pages Requested\r\n");
    }

    paddr_t pAddress;
    uint32_t alignedPagesCount = pow2RoundUp(pages);

    uint32_t levelToLook = (MEM_LEVELS-1)-bitscan(alignedPagesCount);
    uint32_t currentLevel = levelToLook;

    uint32_t indexFound;

    bool memoryFound = false;
    do {
        if (currentLevel >= MEM_LEVELS) {
            kpanic("No More Memory Left to Allocate");
        }
        
        for (indexFound = 0; indexFound < (1U << currentLevel); indexFound++) {
            if ((allocatorNodes[levelOffset(currentLevel) + indexFound] & ALLOCATOR_NODE_VALID) && !(allocatorNodes[levelOffset(currentLevel) + indexFound] & ALLOCATOR_NODE_SPLIT) && !(allocatorNodes[levelOffset(currentLevel) + indexFound] & ALLOCATOR_NODE_ALLOCATED)) {
                memoryFound = true;
                break;
            }
        }
        if (!memoryFound) {
            currentLevel--;
        }
    } while (!memoryFound);
    
    while (currentLevel < levelToLook) {
        allocatorNodes[levelOffset(currentLevel) + indexFound] |= ALLOCATOR_NODE_SPLIT | ALLOCATOR_NODE_VALID;
        if (currentLevel < (MEM_LEVELS-1)) {
            allocatorNodes[levelOffset(currentLevel+1) + 2*indexFound] |= ALLOCATOR_NODE_VALID;
            allocatorNodes[levelOffset(currentLevel+1) + 2*indexFound+1] |= ALLOCATOR_NODE_VALID;
            currentLevel++;
        }
        // this is the same as indexFoudn *= 2 but eh 
        indexFound = indexFound << 1;
    }
    size_t offset = (indexFound * (PAGE_SIZE<<((MEM_LEVELS-1)-currentLevel)));
    
    allocatorNodes[levelOffset(currentLevel) + indexFound] |= ALLOCATOR_NODE_ALLOCATED;
    pAddress = allocatorRamBegin + offset;
    memset((void *) pAddress, 0, pages * PAGE_SIZE);
    return pAddress;
}


void deallocPage(paddr_t pAddress, size_t pages) {
    uint32_t alignedPagesCount = pow2RoundUp(pages);
    if (pages > MEM_MAX_ALLOCATE_SIZE || pages == 0) {
        kpanic("Amount of Pages Requested To Deallocate is Invalid");
    }
    uint32_t levelToLook = (MEM_LEVELS-1)-bitscan(alignedPagesCount);
    uint32_t currentLevel = levelToLook;
    size_t offsetInMemory = pAddress - allocatorRamBegin;
    uint32_t indexInTree = offsetInMemory / (PAGE_SIZE<<((MEM_LEVELS-1)-currentLevel));

    if ((allocatorNodes[levelOffset(currentLevel) + indexInTree] & ALLOCATOR_NODE_SPLIT) || !(allocatorNodes[levelOffset(currentLevel) + indexInTree] & ALLOCATOR_NODE_VALID)) {
        kpanic("Deallocation Address is Invalid");
    }
    if (!(allocatorNodes[levelOffset(currentLevel) + (indexInTree ^ 1)] & ALLOCATOR_NODE_VALID)) {
        kpanic("Allocator Broken, Buddy Somehow Isnt Valid");
    }

    bool pairFound = false;
    do {
        // FREE CURRENT NODE
        allocatorNodes[levelOffset(currentLevel) + indexInTree] &= 0;
        allocatorNodes[levelOffset(currentLevel) + indexInTree] |= ALLOCATOR_NODE_VALID;
        if (!(allocatorNodes[levelOffset(currentLevel) + (indexInTree ^ 1)] & ALLOCATOR_NODE_SPLIT) && !(allocatorNodes[levelOffset(currentLevel) + (indexInTree ^ 1)] & ALLOCATOR_NODE_ALLOCATED) && currentLevel > 0) { // CHECK IF BUDDY IS AVAILABLE
            // DE-VALID BOTH AND STEP DOWN A LEVEL
            allocatorNodes[levelOffset(currentLevel) + (indexInTree ^ 1)] &= 0;
            allocatorNodes[levelOffset(currentLevel) + indexInTree] &= 0;
            // DIVIDE BY 2 TO GET THE INDEX IN THE LEVEL ABOVE
            indexInTree = indexInTree >> 1;
            currentLevel--;
            pairFound = true;
        } else {
            pairFound = false;
        }
    } while (pairFound);
}
