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
#include "drivers/mmio.h"

#define GPFSEL0     (PERIPHERAL_BASE + 0x200000)
#define GPFSEL1     (PERIPHERAL_BASE + 0x200004)
#define GPSET0      (PERIPHERAL_BASE + 0x20001C)
#define GPCLR0      (PERIPHERAL_BASE + 0x200028)
#define GPPUPPDN0   (PERIPHERAL_BASE + 0x2000E4)