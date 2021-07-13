#include "../string.h"

static String_t Create(char const * const pointer, max_fast_t length) {
    String_t s = {
        .array_base = {
            .pointer = pointer,
            .count = length
        }
    };
    return s;
}

static bool Compare(
    String_t const * const s1,
    String_t const * const s2
) {
    const size_t element_size = sizeof(*s1->array_base.pointer); // 1 byte
    Array_t *a1 = ToArrayBase(s1);
    Array_t *a2 = ToArrayBase(s2);
    return arrayMethods.Compare(a1, a2, element_size);
}

static char const * FindSequence(
    String_t const * const s1,
    String_t const * const s2
) {
    const size_t element_size = sizeof(*s1->array_base.pointer); // 1 byte
    Array_t *a1 = ToArrayBase(s1);
    Array_t *a2 = ToArrayBase(s2);
    return arrayMethods.FindSequence(a1, a2, element_size);
}

String_t SimpleClone(String_t const * const s) {
    Array_t *a = ToArrayBase(s);
    return stringMethods.Create(a->pointer, a->count);
}


struct _StringMethods stringMethods = {
    .Compare        = Compare,
    .FindSequence   = FindSequence,
    .Create         = Create,
    .SimpleClone    = SimpleClone
};