#include "array.h"



Array_T Array_new(int length) 
{
    Array_T a = malloc(sizeof(*a));
    a->arr = malloc(sizeof(uint32_t) * length);
    a->length = length;
    return a;
}

void Array_put(Array_T a, int index, uint32_t val) 
{
    (a->arr)[index] = val;
}

uint32_t Array_get(Array_T a, int index) 
{
    return (a->arr)[index];
}

unsigned Array_length(Array_T a) 
{
    return a->length;
}
void Array_free(Array_T *a)
 {
    free((*a)->arr);
    free(*a);
}
