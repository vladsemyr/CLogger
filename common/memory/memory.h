#ifndef COMMON_MEMORY_MEMORY_H
#define COMMON_MEMORY_MEMORY_H

#include "../types/types.h"

extern struct _MemoryMethods {
    bool (*FastCompare)(void const * p1, void const * p2, max_fast_t const len);
    bool (*Compare)(void const * p1, void const * p2, max_fast_t const len);
} memoryMethods;

#endif