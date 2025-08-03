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

#include "utils/common.h"

size_t bitscan(size_t x) {
    if(x == 0) return 0x0;
    x = x & -x;
    size_t ret = 0;
    if(x & 0xFFFFFFFF00000000) ret += 32;
    if(x & 0xFFFF0000FFFF0000) ret += 16;
    if(x & 0xFF00FF00FF00FF00) ret += 8;
    if(x & 0xF0F0F0F0F0F0F0F0) ret += 4;
    if(x & 0xCCCCCCCCCCCCCCCC) ret += 2;
    if(x & 0xAAAAAAAAAAAAAAAA) ret += 1;
    return ret;
}

size_t pow2RoundUp(size_t x) {
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x++;
    return x;
}

size_t pow(size_t x, size_t power) {
    if (power == 0) return 1;
    size_t result = x;
    for (size_t i = 1; i < power; i++) {
        result *= x;
    }
    return result;
}