#include "common.h"
#include "heap.h"
#include "memory.h"
#include "kprintf.h"
static uint8_t heapNodes[BITMAP_LENGTH];
static paddr_t heapRamBegin;

static inline uint32_t levelOffset(uint32_t x) {
    return (1U << x) -1;
}

void initHeap(paddr_t __heap) {
    memset(&heapNodes, 0, BITMAP_LENGTH);
    
    heapNodes[0] |= ALLOCATOR_NODE_VALID;
    heapRamBegin = __heap;
}

void *kalloc(uint64_t bytes) {
    if (bytes < CHUNK_SIZE) {
        kprintf("Small malloc\r\n");
        bytes = CHUNK_SIZE;
    }
    bytes = pow2RoundUp(bytes);
    kprintf("New Size: %d\r\n", bytes);

    uint32_t levelToLook = (LEVELS-1)-bitscan(bytes/128);
    uint32_t currentLevel = levelToLook;
    uint32_t indexFound;
    bool memoryFound = false;

    do {
        if (currentLevel >= LEVELS) {
            kpanic("Out Of Heap Space");
        }
        
        for (indexFound = 0; indexFound < (1U << currentLevel); indexFound++) {
            if ((heapNodes[levelOffset(currentLevel) + indexFound] & ALLOCATOR_NODE_VALID) && !(heapNodes[levelOffset(currentLevel) + indexFound] & ALLOCATOR_NODE_SPLIT) && !(heapNodes[levelOffset(currentLevel) + indexFound] & ALLOCATOR_NODE_ALLOCATED)) {
                memoryFound = true;
                break;
            }
        }
        if (!memoryFound) {
            currentLevel--;
        }
    } while (!memoryFound);
    
    while (currentLevel < levelToLook) {
        heapNodes[levelOffset(currentLevel) + indexFound] |= ALLOCATOR_NODE_SPLIT | ALLOCATOR_NODE_VALID;
        if (currentLevel < (LEVELS-1)) {
            heapNodes[levelOffset(currentLevel+1) + 2*indexFound] |= ALLOCATOR_NODE_VALID;
            heapNodes[levelOffset(currentLevel+1) + 2*indexFound+1] |= ALLOCATOR_NODE_VALID;
            currentLevel++;
        }
        // this is the same as indexFoudn *= 2 but eh 
        indexFound = indexFound << 1;
    }
    uint64_t offset = (indexFound * (CHUNK_SIZE<<((LEVELS-1)-currentLevel)));
    heapNodes[levelOffset(currentLevel) + indexFound] |= ALLOCATOR_NODE_ALLOCATED;
    uint8_t *adr =(uint8_t *)(heapRamBegin + offset);

    memset(adr, 0, bytes);
    return adr;
}

