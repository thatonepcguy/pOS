#include "utils/memory.h"
#include "utils/common.h"

void *memset(void *buf, char c, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    /// set a certain region in memory to a char
    while (n--) {
        *p++ = c;
    }
    return buf;
}

void *memcpy(void *dst, const void *src, size_t n) {
    // cast to acess individual bytes
    uint8_t *d = (uint8_t *) dst;
    const uint8_t *s = (const uint8_t *) src;

    while (n--) {
        *d++ = *s++;
    }

    return dst;
}