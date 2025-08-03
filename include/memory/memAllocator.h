/*
    * raspix is a custom OS designed to function on the Raspberry Pi 4b.
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

#pragma once
#include "utils/common.h"

#define PAGE_SIZE (1024*4)

#define MEM_MAX_ALLOCATE_SIZE ((size_t)((2ULL*1024ULL*1024ULL*1024ULL) / PAGE_SIZE)) /* 1GB  In Pages*/
#define MEM_LEVELS 20 // log2(MAX_ALLOCATE_SIZE) + 1
#define MEM_BITMAP_LENGTH ((1U << MEM_LEVELS) )

#define ALLOCATOR_NODE_VALID 0x1
#define ALLOCATOR_NODE_SPLIT 0x2
#define ALLOCATOR_NODE_ALLOCATED 0x4

void initAllocator(paddr_t __ram_start);
paddr_t allocPages(size_t pages);
void deallocPages(paddr_t pAddress);