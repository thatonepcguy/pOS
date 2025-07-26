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

#pragma once
#include "utils/common.h"

#define PTE_VALID       (1ULL<<0)
#define PTE_TABLEPAGE   (1ULL<<1)
#define PTE_AF          (1ULL<<10)

#define PTE_ADDRESS_MASK 0x000000FFFFFFF000

void mapPage(vaddr_t vAddress, paddr_t pAddress, uint8_t attrIndx);
void demapPage(vaddr_t vAddress);