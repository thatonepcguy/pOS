#pragma once
#include "utils/common.h"

static inline void mmioWrite(const uint64_t adr, uint32_t val) {
    *(volatile uint32_t *)(adr) = val;
}

static inline uint32_t mmioRead(const uint64_t adr) {
    return *(volatile uint32_t *)(adr);
}