#ifndef COMMON_ARRAY_ARRAY_H
#define COMMON_ARRAY_ARRAY_H

#include "../types/types.h"

#define __ArrayDef(type)    \
    const type *pointer;    \
    max_fast_t count;

typedef struct Array {
    __ArrayDef(void)
} Array_t;

#define ArrayBase(type)     \
    struct {                \
        __ArrayDef(type)    \
    } array_base;


#define ToArrayBase(ptr_x)  ((Array_t *)(&(ptr_x->array_base)))


extern struct _ArrayMethods {
    bool         (*Compare)      (Array_t const * const a1, Array_t const * const a2, size_t const element_size);
    void const * (*Find)         (Array_t const * const s, void const * const element, size_t const element_size);
    void const * (*FindSequence) (Array_t const * const array, Array_t const * const sequence, size_t const element_size);
} arrayMethods;


#endif