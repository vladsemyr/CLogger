#include "../array.h"
#include <assert.h>
#include "../../types/types.h"

#include "../../memory/memory.h"


static bool Compare(
    struct SimpleArray const * const array_1,
    struct SimpleArray const * const array_2,
    size_t const element_size
) {
    if (array_1->count != array_2->count)
        return false;
    
    register_t const array_byte_len = array_1->count * element_size;
    return memoryMethods.FastCompare(array_1->pointer, array_2->pointer, array_byte_len);
}

static void const * Find(
    struct SimpleArray const * const a,
    void               const * const element,
    size_t                     const element_size
) {
    minimal_size_t const *       pointer_a = ((minimal_size_t const *) a->pointer);
    minimal_size_t const * const last_pointer_s = pointer_a + (a->count * element_size);
    minimal_size_t const * const pointer_find_element = (minimal_size_t const * const) element;
    
    while (pointer_a != last_pointer_s) {
        // сравнение памяти размера element_size
        minimal_size_t const * p1 = pointer_a;
        minimal_size_t const * p2 = pointer_find_element;
        bool is_elements_equal = memoryMethods.Compare(p1, p2, element_size);
        if (is_elements_equal)
            return pointer_a;
        
        pointer_a += element_size;
    }
    
    return NULL;
}

static void const * FindSequence(
    struct SimpleArray const * const array,
    struct SimpleArray const * const sequence,
    size_t                     const element_size
) {
    if (sequence->count > array->count)
        return NULL;
    
    minimal_size_t const * pointer_a = ((minimal_size_t const *) array->pointer);
    minimal_size_t const * last_pointer_a = pointer_a + (array->count * element_size);
    register_t const sequence_byte_len = sequence->count * element_size;
    
    
    while (pointer_a != last_pointer_a) {
        bool is_seq_equal = memoryMethods.FastCompare(pointer_a, sequence->pointer, sequence_byte_len);
        if (is_seq_equal)
            return pointer_a;
        pointer_a++;
    }
    
    return NULL;
}


struct _ArrayMethods arrayMethods ={
    .Compare = Compare,
    .Find = Find,
    .FindSequence = FindSequence
};