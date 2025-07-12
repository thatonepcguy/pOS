#include "common.h"
#include "heap.h"
#include "memory.h"
#include "kprintf.h"
static uint8_t heapNodes[HEAP_BITMAP_LENGTH];
static paddr_t heapRamBegin;

static inline uint32_t levelOffset(uint32_t x) {
    return (1U << x) -1;
}

void initHeap(paddr_t __heap) {
    memset(&heapNodes, 0, HEAP_BITMAP_LENGTH);
    
    heapNodes[0] |= ALLOCATOR_NODE_VALID;
    heapRamBegin = __heap;
}

// kernel malloc
void *kalloc(uint64_t bytes) {
    if (bytes < CHUNK_SIZE) {
        bytes = CHUNK_SIZE;
    }
    bytes = pow2RoundUp(bytes);

    uint32_t levelToLook = (HEAP_LEVELS-1)-bitscan(bytes/128);
    uint32_t currentLevel = levelToLook;
    uint32_t indexFound;
    bool memoryFound = false;

    do {
        if (currentLevel >= HEAP_LEVELS) {
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
        heapNodes[levelOffset(currentLevel) + indexFound] |= ALLOCATOR_NODE_SPLIT;
        heapNodes[levelOffset(currentLevel) + indexFound] |= ALLOCATOR_NODE_VALID;
        if (currentLevel < (HEAP_LEVELS-1)) {
            heapNodes[levelOffset(currentLevel+1) + 2*indexFound] |= ALLOCATOR_NODE_VALID;
            heapNodes[levelOffset(currentLevel+1) + 2*indexFound+1] |= ALLOCATOR_NODE_VALID;
            currentLevel++;
        }
        // this is the same as indexFoudn *= 2 but eh 
        indexFound = indexFound << 1;
    }
    uint64_t offset = (indexFound * (CHUNK_SIZE<<((HEAP_LEVELS-1)-currentLevel)));
    heapNodes[levelOffset(currentLevel) + indexFound] |= ALLOCATOR_NODE_ALLOCATED;
    void *adr = (void *)(heapRamBegin + offset);

    return adr;
}

// kernel free
void kfree(void *adr) {

    uint32_t levelToLook = (HEAP_LEVELS-1);
    uint32_t currentLevel = levelToLook;
    uint64_t offsetInHeap = (uint64_t)adr - heapRamBegin;
    uint32_t indexInTree = offsetInHeap / (CHUNK_SIZE<<((HEAP_LEVELS-1)-currentLevel));

    bool pairFound = false;
    bool foundStart = false;
    do {
        // i dont wanna store extra metadata so im sacrificing an ever so slight amount of speed for less storage and complexity
        if (!is_aligned(offsetInHeap, (CHUNK_SIZE<<((HEAP_LEVELS-1)-currentLevel))) && !foundStart)
            kpanic("Invalid Heap Free");
        // if its not valid but its aligned we step down a level cause this node is invalid
        if (!(heapNodes[levelOffset(currentLevel) + indexInTree] & ALLOCATOR_NODE_VALID) && !foundStart) {
            indexInTree = indexInTree >> 1;
            currentLevel--;
            continue;
        } else if ((heapNodes[levelOffset(currentLevel) + indexInTree] & ALLOCATOR_NODE_VALID) && !foundStart) {
            foundStart = true;
        }

        // FREE CURRENT NODE
        heapNodes[levelOffset(currentLevel) + indexInTree] &= 0;
        heapNodes[levelOffset(currentLevel) + indexInTree] |= ALLOCATOR_NODE_VALID;
        if (!(heapNodes[levelOffset(currentLevel) + (indexInTree ^ 1)] & ALLOCATOR_NODE_SPLIT) && !(heapNodes[levelOffset(currentLevel) + (indexInTree ^ 1)] & ALLOCATOR_NODE_ALLOCATED) && currentLevel > 0) { // CHECK IF BUDDY IS AVAILABLE
            // DE-VALID BOTH AND STEP DOWN A LEVEL
            heapNodes[levelOffset(currentLevel) + (indexInTree ^ 1)] &= 0;
            heapNodes[levelOffset(currentLevel) + indexInTree] &= 0;
            // DIVIDE BY 2 TO GET THE INDEX IN THE LEVEL ABOVE
            indexInTree = indexInTree >> 1;
            currentLevel--;
            pairFound = true;
        } else {
            pairFound = false;
        }
    } while (pairFound);
}

void *krealloc(void *adr, size_t resBytes) {
    if (adr == NULL) 
        return kalloc(resBytes);
    if (resBytes == 0) {
        kfree(adr);
        return NULL;
    }
    if (resBytes < 128) 
        resBytes = 128;

    resBytes = pow2RoundUp(resBytes);
    
    // find initial size of adr
    uint32_t levelToLook = (HEAP_LEVELS-1);
    uint32_t currentLevel = levelToLook;
    uint64_t offsetInHeap = (uint64_t)adr - heapRamBegin;
    uint32_t indexInTree = offsetInHeap / (CHUNK_SIZE<<((HEAP_LEVELS-1)-currentLevel));

    bool foundStart = false;
    
     do {
        // i dont wanna store extra metadata so im sacrificing an ever so slight amount of speed for less storage and complexity
        if (!is_aligned(offsetInHeap, (CHUNK_SIZE<<((HEAP_LEVELS-1)-currentLevel))) && !foundStart)
            kpanic("Invalid Heap Realloc");
        // if its not valid but its aligned we step down a level cause this node is invalid
        if (!(heapNodes[levelOffset(currentLevel) + indexInTree] & ALLOCATOR_NODE_VALID) && !foundStart) {
            indexInTree = indexInTree >> 1;
            currentLevel--;
            continue;
        } else if ((heapNodes[levelOffset(currentLevel) + indexInTree] & ALLOCATOR_NODE_VALID) && !foundStart) {
            foundStart = true;
        } 
        
    } while (!foundStart);

    size_t oldSize = (CHUNK_SIZE<<((HEAP_LEVELS-1)-currentLevel));
    uint8_t *newAdr = kalloc(resBytes);


    if (oldSize <= resBytes) {
        memcpy(newAdr, adr, oldSize);
    } else if (oldSize > resBytes) {
        memcpy(newAdr, adr, resBytes);
    }

    kfree(adr);
    return newAdr;
}