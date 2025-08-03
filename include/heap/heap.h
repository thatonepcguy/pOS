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

#define CHUNK_SIZE 128

#define HEAP_MAX_ALLOCATE_SIZE 4*1024*1024 / CHUNK_SIZE /* 16MB heap in chunks*/
#define HEAP_LEVELS 16
#define HEAP_BITMAP_LENGTH ((1U << HEAP_LEVELS) )

#define ALLOCATOR_NODE_VALID 0x1
#define ALLOCATOR_NODE_SPLIT 0x2
#define ALLOCATOR_NODE_ALLOCATED 0x4

void initHeap(paddr_t __heap);

void *kalloc(uint64_t bytes);
void kfree(void *adr);
void *krealloc(void *adr, size_t resBytes);