#include "identifiers.h"

Identifier_T Ident_new(unsigned capacity) 
{
    Identifier_T i = malloc(sizeof(*i));
    i->ident = malloc(sizeof(*(i->ident)) * capacity);
    i->size = 0;
    i->capacity = 0;
    return i;
}

unsigned Ident_get(Identifier_T i, unsigned index) 
{
    return (i->ident)[index];
}

void Ident_put(Identifier_T i, unsigned index, unsigned elem) 
{
    (i->ident)[index] = elem;
}

static void resize(Identifier_T i)
{
    unsigned newCap = i->capacity * 2 + 1;
    unsigned *temp = malloc(sizeof(temp) * newCap);
    unsigned size = i->size;
    for(unsigned z = 0; z < size; z ++ ) {
        temp[z] = (i->ident)[z];
    }
    free(i->ident);
    (i->capacity) = newCap;
    (i->ident)= temp;
    // free(s);

    // return s;
}

unsigned Ident_length(Identifier_T i) 
{
    return i->size;
}

void Ident_push(Identifier_T i, unsigned elem) 
{
    if(i->size == i->capacity) {
        resize(i);
    }
    (i->ident)[i->size] = elem;
    (i->size)++;
}

extern unsigned Ident_pop(Identifier_T i) {
    return i->ident[--(i->size)];
}

void Ident_free(Identifier_T *i) 
{
    free((*i)->ident);
    free(*i);
}

