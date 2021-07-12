#include <assert.h>
#include "../memory.h"


enum StaticCompute {
    MINIMAL_SIZE = sizeof(minimal_size_t),      // TODO: ???
    WORD_SIZE = sizeof(register_t),             // обычно 4 или 8 байт
    WORD_SIZE_LOG2_1 = WORD_SIZE / 2,
    WORD_SIZE_LOG2_2 = WORD_SIZE_LOG2_1 / 2,
    WORD_SIZE_LOG2_3 = WORD_SIZE_LOG2_2 / 2,
    WORD_SIZE_LOG2_4 = WORD_SIZE_LOG2_3 / 2,
    WORD_SIZE_LOG2_5 = WORD_SIZE_LOG2_4 / 2,
    WORD_SIZE_LOG2_6 = WORD_SIZE_LOG2_5 / 2,
    WORD_SIZE_LOG2_7 = WORD_SIZE_LOG2_6 / 2,
    WORD_SIZE_LOG2_8 = WORD_SIZE_LOG2_7 / 2,
    WORD_SIZE_LOG2_9 = WORD_SIZE_LOG2_8 / 2,
    WORD_SIZE_LOG2_SHIFT = 
        WORD_SIZE_LOG2_1 == 1 ? 1 :
        WORD_SIZE_LOG2_2 == 1 ? 2 :
        WORD_SIZE_LOG2_3 == 1 ? 3 :
        WORD_SIZE_LOG2_4 == 1 ? 4 :
        WORD_SIZE_LOG2_5 == 1 ? 5 :
        WORD_SIZE_LOG2_6 == 1 ? 6 :
        WORD_SIZE_LOG2_7 == 1 ? 7 :
        WORD_SIZE_LOG2_8 == 1 ? 8 :
        WORD_SIZE_LOG2_9 == 1 ? 9 : 0
};
static_assert(WORD_SIZE_LOG2_SHIFT != 0, "Shift == 0!");
static_assert((WORD_SIZE & (WORD_SIZE - 1)) == 0, "WORD_SIZE is not power of 2!");

static bool FastCompare(void const * p1, void const * p2, register_t const len) {
    register_t const         whole_parts_count  = len >> WORD_SIZE_LOG2_SHIFT; // делится может долго, поэтому сдвиги
    register_t const         residue            = len - (whole_parts_count << WORD_SIZE_LOG2_SHIFT);
    register_t const * const last_whole_part_a1 = ((register_t const * const) p1) + whole_parts_count;
    register_t const *       pointer_whole_a1   = ((register_t const *) p1);
    register_t const *       pointer_whole_a2   = ((register_t const *) p2);
    
    while (pointer_whole_a1 != last_whole_part_a1) {
        if (*pointer_whole_a1 != *pointer_whole_a2)
            return false;
        pointer_whole_a1++;
        pointer_whole_a2++;
    }
    
    minimal_size_t const * const last_residue_part_a1 = ((minimal_size_t const * const) last_whole_part_a1) + residue;
    minimal_size_t const *       pointer_residue_a1   = ((minimal_size_t const *) pointer_whole_a1);
    minimal_size_t const *       pointer_residue_a2   = ((minimal_size_t const *) pointer_whole_a2);
    
    while (pointer_residue_a1 != last_residue_part_a1) {
        if (*pointer_residue_a1 != *pointer_residue_a2)
            return false;
        pointer_residue_a1++;
        pointer_residue_a2++;
    }
    
    return true;
}

static bool Compare(void const * p1, void const * p2, register_t const len) {
    // TODO: побайтно
    return FastCompare(p1, p2 ,len);
}

struct _MemoryMethods memoryMethods = {
    .FastCompare = FastCompare,
    .Compare = Compare
};