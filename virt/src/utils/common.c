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