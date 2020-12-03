#include "sequence.h"

Sequence_T Sequence_new(unsigned capacity) 
{
    Sequence_T s = malloc(sizeof(*s));
    s->seq = malloc(sizeof(*(s->seq)) * capacity);
    s->size = 0;
    s->capacity = 0;
    return s;
}

Array_T Sequence_get(Sequence_T s, unsigned index) 
{
    return (s->seq)[index];
}

void Sequence_put(Sequence_T s, unsigned index, Array_T elem) 
{
    (s->seq)[index] = elem;
}

void resize(Sequence_T s)
{
    unsigned newCap = s->capacity * 2 + 1;
    Array_T *temp = malloc(sizeof(temp) * newCap);
    unsigned size = s->size;
    for(unsigned i = 0; i < size; i ++ ) {
        temp[i] = (s->seq)[i];
    }
    free(s->seq);
    (s->capacity) = newCap;
    (s->seq)= temp;
    // free(s);

    // return s;
}

unsigned Sequence_length(Sequence_T s) 
{
    return s->size;
}

void Sequence_push(Sequence_T s, Array_T elem) 
{
    if(s->size == s->capacity) {
        resize(s);
    }
    (s->seq)[s->size] = elem;
    (s->size)++;
}

void Sequence_free(Sequence_T *s) 
{
    // Sequence_T seq_temp = *s;
    // unsigned length = seq_temp->size;
    // for (unsigned i = 0; i < length; i++) {
    //     free(((seq_temp->seq)[i])->arr);
    //     free(seq_temp->seq[i]);
    // }
    free((*s)->seq);
    free(*s);
}

