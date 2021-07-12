#ifndef COMMON_STRING_STRING_H
#define COMMON_STRING_STRING_H

#include "../array/array.h"
#include <stdbool.h>

struct String {
    ArrayBase(char);
    
};


extern struct _StringMethods {
    bool (*Compare)(struct String const * const s1, struct String const * const s2);
    char const * (*FindSequence)(struct String const * const s1, struct String const * const s2);
} stringMethods;

#endif