#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef ARRAY_T
#define ARRAY_T

typedef struct Array_T {
    uint32_t *arr;
    unsigned length;
} * Array_T;

extern Array_T Array_new(int length);
extern void Array_put(Array_T a, int index, uint32_t val);
extern uint32_t Array_get(Array_T a, int index);
extern unsigned Array_length(Array_T a);
extern void Array_free(Array_T *a);

#endif