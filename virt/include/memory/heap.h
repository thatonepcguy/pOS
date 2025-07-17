#pragma once
#include "utils/common.h"

#define CHUNK_SIZE 128

#define HEAP_MAX_ALLOCATE_SIZE 16*1024*1024 / CHUNK_SIZE /* 16MB heap in chunks*/
#define HEAP_LEVELS 18
#define HEAP_BITMAP_LENGTH ((1U << HEAP_LEVELS) )

#define ALLOCATOR_NODE_VALID 0x1
#define ALLOCATOR_NODE_SPLIT 0x2
#define ALLOCATOR_NODE_ALLOCATED 0x4

void initHeap(paddr_t __heap);

void *kalloc(uint64_t bytes);
void kfree(void *adr);
void *krealloc(void *adr, size_t resBytes);