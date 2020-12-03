#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "array.h"

typedef struct Sequence_T {
    Array_T *seq;
    unsigned size;
    unsigned capacity;
} *Sequence_T;

extern Sequence_T Sequence_new(unsigned capacity);
extern Array_T Sequence_get(Sequence_T s, unsigned index);
extern void Sequence_put(Sequence_T s, unsigned index, Array_T elem);
extern unsigned Sequence_length(Sequence_T s);
extern void resize(Sequence_T s);
extern void Sequence_push(Sequence_T s, Array_T elem);
extern void Sequence_free(Sequence_T *s);
