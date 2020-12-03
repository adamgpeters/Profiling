#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "array.h"

typedef struct Identifier_T {
    unsigned *ident;
    unsigned size;
    unsigned capacity;
} *Identifier_T;

extern Identifier_T Ident_new(unsigned capacity);
extern unsigned Ident_get(Identifier_T s, unsigned index);
extern void Ident_put(Identifier_T s, unsigned index, unsigned elem);
extern unsigned Ident_length(Identifier_T s);
extern void Ident_push(Identifier_T s, unsigned elem);
extern unsigned Ident_pop(Identifier_T s);
extern void Ident_free(Identifier_T *s);
