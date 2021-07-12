#ifndef COMMON_MEMORY_MEMORY_H
#define COMMON_MEMORY_MEMORY_H

#include <stdbool.h>
#include "../types/types.h"

extern struct _MemoryMethods {
    bool (*FastCompare)(void const * p1, void const * p2, register_t const len);
    bool (*Compare)(void const * p1, void const * p2, register_t const len);
} memoryMethods;

#endif