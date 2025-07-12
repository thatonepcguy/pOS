#pragma once
#include "common.h"

#define PAGE_SIZE (1024*64)

#define MEM_MAX_ALLOCATE_SIZE ((1024 * 1024 * 1024) / PAGE_SIZE) /* 1GB  In Pages*/
#define MEM_LEVELS 15 // log2(MAX_ALLOCATE_SIZE) + 1
#define MEM_BITMAP_LENGTH ((1U << MEM_LEVELS) )

#define ALLOCATOR_NODE_VALID 0x1
#define ALLOCATOR_NODE_SPLIT 0x2
#define ALLOCATOR_NODE_ALLOCATED 0x4

void initAllocator(paddr_t __ram_start);
paddr_t allocPage(size_t pages);
void deallocPage(paddr_t pAddress, size_t pages);