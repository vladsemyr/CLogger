#ifndef COMMON_ARRAY_ARRAY_H
#define COMMON_ARRAY_ARRAY_H

#include <stddef.h>
#include <stdbool.h>

struct SimpleArray {
    void *pointer;
    size_t count;
};

#define ArrayBase(type)             \
    union {                         \
        type *_pointer;             \
        struct SimpleArray _array;  \
    } _arraybase

#define ArrayBaseImplementation(type)   \
    static inline int name ## Compare(type *a1, type *a2) {             \
        return _ArrayCompare((void *) a1, (void * ) a2, sizeof(type));  \
    }

#define TemplateArray(name, type)   \
    struct name {                   \
        type *pointer;              \
        size_t count;               \
    };                              \
                                    \
    static inline int name ## Compare(type *a1, type *a2) {             \
        return _ArrayCompare((void *) a1, (void * ) a2, sizeof(type));  \
    }

extern struct _ArrayMethods {
    bool         (*Compare)      (struct SimpleArray const * const a1, struct SimpleArray const * const a2, size_t const element_size);
    void const * (*Find)         (struct SimpleArray const * const s, void const * const element, size_t const element_size);
    void const * (*FindSequence) (struct SimpleArray const * const array, struct SimpleArray const * const sequence, size_t const element_size);
} arrayMethods;


#endif