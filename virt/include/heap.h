#include "common.h"

#define CHUNK_SIZE 128

#define MAX_ALLOCATE_SIZE 16*1024*1024 / CHUNK_SIZE /* 16MB heap in chunks*/
#define LEVELS 18
#define BITMAP_LENGTH ((1U << LEVELS) )

#define ALLOCATOR_NODE_VALID 0x1
#define ALLOCATOR_NODE_SPLIT 0x2
#define ALLOCATOR_NODE_ALLOCATED 0x4

void initHeap(paddr_t __heap);

void *kalloc(uint64_t bytes);
void kfree(void *adr);