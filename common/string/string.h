#ifndef COMMON_STRING_STRING_H
#define COMMON_STRING_STRING_H

#include "../array/array.h"

typedef struct String {
    ArrayBase(char);
} String_t;


extern struct _StringMethods {
    bool            (*Compare)(String_t const * const s1, String_t const * const s2);
    char const *    (*FindSequence)(String_t const * const s1, String_t const * const s2);
    String_t        (*Create)(char const * const pointer, max_fast_t length);
    String_t        (*SimpleClone)(String_t const * const s);
} stringMethods;

#endif