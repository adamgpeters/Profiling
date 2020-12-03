/****************************************************************************
 *  COMP 40 HW6 Universal Machine                                           *
 *                                                                          *
 *  mem_seq.c                                                               *
 *  Complete Memory Sequence Implementation                                 *
 *  Created By (UTLN): jlai03 & apeter09                                    *
 *           On      : 11/22/2020                                           *
 *                                                                          *
 ****************************************************************************/


#include "mem_seq.h"
#include "registers.h"
#include "array.h"

/******************* STATIC FUNCTION DECLARATIONS ****************************/
// static void pushIdentifier(UArray_T *identifiers, unsigned i);
// static UArray_T resize(UArray_T identifiers);

/******************* MEMORY CREATE AND FREE **********************************/
Mem_Seq Mem_new(int mem_len) 
{
    /* Create Struct */
    // assert(mem_len >= 0);
    Mem_Seq seq = malloc(sizeof(*seq));

    /* Create Memory Sequence */
    // assert(seq != NULL);
    seq->memory = Sequence_new(mem_len);

    /* Create Identifier UArray */
    seq->identifiers = Ident_new(20);
    // seq->identifiers = UArray_new(20, sizeof(unsigned));    
    // *((unsigned *) UArray_at(seq->identifiers, 0)) = 1;
    return seq; 
}

void Mem_free_all(Mem_Seq *m) 
{
    // assert(m != NULL);
    Sequence_T memory = (*m)->memory;
    Identifier_T identifiers = (*m)->identifiers;

    /* Free Segments */
    int length = Sequence_length(memory);

    for (int i = 0; i < length; i++){

        Array_T segment = (memory->seq)[i];
        if(segment != NULL){
                Array_free(&segment);
        }
    }

    /* Free Memory, Identifier, and Struct */
    Sequence_free(&memory);
    Ident_free(&identifiers);
    free(*m);
}

/******************* MEMORY SEGMENT FUNCTIONS ********************************/
unsigned Mem_addseg(Mem_Seq m, int length) 
{
    
    /* Initialize Segment */
    Array_T seg = Array_new(length);
    if (seg == NULL) {
        return 0;
    }

    for (int i = 0; i < length; i++) {
        (seg->arr)[i] = 0;
        // Array_put(seg,i, 0);
        // *elem = 0;
    }
    /* Addding the Segment */
    // unsigned placement;
    if ((m->identifiers->size) == 0) {
        // Sequence_push(m->memory, seg);
        Sequence_T s = m->memory;
        if(s->size == s->capacity) {
            resize(s);
        }
        (s->seq)[s->size] = seg;
        (s->size)++;

        return (s->size) - 1;
    } else {
        unsigned seqIndex = Ident_pop(m->identifiers);

        (m->memory->seq)[seqIndex] = seg;
        // Sequence_put(m->memory, seqIndex, seg);  
        return seqIndex;             
    }
    // return placement;
}

uint32_t Mem_seg_get(Mem_Seq m, int seg_index, int index) 
{
    return Array_get((m->memory->seq)[seg_index], index);
}

void Mem_seg_put(Mem_Seq m, int seg_index, int index, uint32_t val) 
{
    Array_put((m->memory->seq)[seg_index], index, val);
}

int  Mem_seglength(Mem_Seq m, int seg_index) 
{    
    // assert (m!= NULL && seg_index >= 0);
    return Array_length((m->memory->seq)[seg_index]);
}  

void Mem_freeseg(Mem_Seq m, int seg_index) 
{   
    // assert(m!= NULL && seg_index >= 0);
    Array_T seg = (m->memory->seq)[seg_index];
    if (seg != NULL) {
        /* Push index to Identifiers */
        if (seg_index != 0) {
            Ident_push(m->identifiers, seg_index);
            // pushIdentifier(&(m->identifiers), seg_index); 
        }
        /* Free Segment */
        Array_free(&seg);
        Sequence_put(m->memory, seg_index, NULL);
    }
}   

void Mem_load(Mem_Seq m, int seg_index) 
{
    // assert(m != NULL && seg_index >= 0 && seg_index < Seq_length(m->memory));
    if (seg_index == 0) {
        return;
    }
    /* Create copy of segment and copy over info */
    Array_T to_copy = (m->memory->seq)[seg_index];     
    int length = Array_length(to_copy);
    Array_T new_seg = Array_new(length);
    for (int i  = 0; i < length; i++){
        uint32_t from = Array_get(to_copy, i);
        Array_put(new_seg, i, from);
        // *to = *from;
    }   
    /* Free previous segment and load into the first index */
    Mem_freeseg(m, 0);
    Sequence_put(m->memory,0, new_seg);
}  

/******************* IDENTIFIER ARRAY FUNCTIONS ******************************/
// static void pushIdentifier(UArray_T *identifiers, unsigned i) 
// {
//     // assert(identifiers != NULL);
//     /* Add index to Uarray */
//     unsigned *size = UArray_at(*identifiers, 0);
//     if (*size == (unsigned)UArray_length(*identifiers)) {
//         *identifiers = resize(*identifiers); 
//     }
//     size = UArray_at(*identifiers, 0);

//     /* Update size */
//     unsigned *elem = UArray_at(*identifiers, *size);
//     *elem = i;
//     (*size) += 1;
// }

// static UArray_T resize(UArray_T identifiers) 
// {
//     // assert(identifiers != NULL);
//     unsigned capacity = UArray_length(identifiers);
//     unsigned newCapacity = capacity * 2 + 1;

//     /* Create new UArray and Copy over info */
//     UArray_T newIdent = UArray_new(newCapacity, sizeof(unsigned));
//     for(unsigned i = 0; i < capacity; i ++) {
//         unsigned *from = UArray_at(identifiers, i);
//         unsigned *to = UArray_at(newIdent, i);
//         *to = *from;
//     }   

//     /* Free previous array and return new array */
//     UArray_free(&identifiers);
//     return newIdent; 
// }  
