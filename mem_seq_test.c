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

/******************* STATIC FUNCTION DECLARATIONS ****************************/
static void pushIdentifier(UArray_T *identifiers, unsigned i);
static UArray_T resize(UArray_T identifiers);

/******************* MEMORY CREATE AND FREE **********************************/
Mem_Seq Mem_new(int mem_len) 
{
    /* Create Struct */
    assert(mem_len >= 0);
    Mem_Seq seq = malloc(sizeof(*seq));

    /* Create Memory Sequence */
    assert(seq != NULL);
    seq->memory = Seq_new(mem_len);

    /* Create Identifier UArray */
    seq->identifiers = malloc(sizeof(uint32_t) * 20); 
    (seq->identifiers)[0] = 1;
    return seq; 
}

void Mem_free_all(Mem_Seq *m) 
{
    assert(m != NULL);
    Seq_T memory = (*m)->memory;
    uint32_t *identifiers = (*m)->identifiers;

    /* Free Segments */
    for (int i = 0; i < Seq_length(memory); i++){
        if(Seq_get(memory, i) != NULL){
                uint32_t *segment = Seq_get(memory, i);
                // UArray_free(&segment);
                free(segment);
        }
    }

    /* Free Memory, Identifier, and Struct */
    Seq_free(&memory);
    free(identifiers);
    free(*m);
}

/******************* MEMORY SEGMENT FUNCTIONS ********************************/
unsigned Mem_addseg(Mem_Seq m, int length) 
{
    assert(m != NULL);
    assert(length >= 0);
    
    /* Initialize Segment */
    // UArray_T seg = UArray_new(length, sizeof(uint32_t));
    uint32_t * seg = malloc(sizeof(uint32_t) * length);
    if (seg == NULL) {
        return 0;
    }
    for (int i = 0; i < length; i++) {
        seg[i] = 0;
    }
    /* Addding the Segment */
    unsigned placement;
    if ((m->identifiers)[0] == (unsigned)1) {
        /* Create new Segment */
        Seq_addhi(m->memory, seg);
        placement = Seq_length(m->memory) - 1;
    } else {
        /* Use old index in memory for new segment */
        // uint32_t identIndex = (m->identifiers)[0];  
        uint32_t seqIndex = (m->identifiers)[--((m->identifiers)[0])];
        // (m->identifiers)[0] = identIndex - 1;
        Seq_put(m->memory, seqIndex, seg);  
        placement = seqIndex;             
    }
    return placement;
}

void *Mem_seg_at(Mem_Seq m, int seg_index, int index) 
{
    assert (m!= NULL && seg_index >= 0 && index >= 0); 
    // UArray_T segment = Seq_get(m->memory, seg_index); 
    // assert(segment != NULL);
    return &(((uint32_t *)Seq_get(m->memory, seg_index))[index]);
    // return UArray_at((UArray_T)Seq_get(m->memory, seg_index), index);
}

int  Mem_seglength(Mem_Seq m, int seg_index) 
{
    assert (m!= NULL && seg_index >= 0);
    return UArray_length(Seq_get(m->memory, seg_index));
}  

void Mem_freeseg(Mem_Seq m, int seg_index) 
{   
    assert(m!= NULL && seg_index >= 0);
    if (Seq_get(m->memory, seg_index) != NULL) {
        /* Push index to Identifiers */
        if (seg_index != 0) {
            pushIdentifier(&(m->identifiers), seg_index); 
        }
        /* Free Segment */
        UArray_T segment = Seq_get(m->memory, seg_index);
        UArray_free(&segment);
        Seq_put(m->memory, seg_index, NULL);
    }
}   

void Mem_load(Mem_Seq m, int seg_index) 
{
    assert(m != NULL && seg_index >= 0 && seg_index < Seq_length(m->memory));
    if (seg_index == 0) {
        return;
    }
    /* Create copy of segment and copy over info */
    UArray_T to_copy = Seq_get(m->memory, seg_index);     
    UArray_T new_seg = UArray_new(UArray_length(to_copy), sizeof(uint32_t));
    for (int i  = 0; i < UArray_length(to_copy); i++){
        uint32_t *from = UArray_at(to_copy, i);
        uint32_t *to = UArray_at(new_seg, i);
        *to = *from;
    }   
    /* Free previous segment and load into the first index */

    // seg_instr_length(m, unsigned )

    Mem_freeseg(m, 0);
    Seq_put(m->memory,0, new_seg);
}  

/******************* IDENTIFIER ARRAY FUNCTIONS ******************************/
static void pushIdentifier(UArray_T *identifiers, unsigned i) 
{
    assert(identifiers != NULL);
    /* Add index to Uarray */
    unsigned *size = UArray_at(*identifiers, 0);
    if (*size == (unsigned)UArray_length(*identifiers)) {
        *identifiers = resize(*identifiers); 
    }
    size = UArray_at(*identifiers, 0);

    /* Update size */
    unsigned *elem = UArray_at(*identifiers, *size);
    *elem = i;
    (*size) += 1;
}

static UArray_T resize(UArray_T identifiers) 
{
    assert(identifiers != NULL);
    unsigned capacity = UArray_length(identifiers);
    unsigned newCapacity = capacity * 2 + 1;

    /* Create new UArray and Copy over info */
    UArray_T newIdent = UArray_new(newCapacity, sizeof(unsigned));
    for(unsigned i = 0; i < capacity; i ++) {
        unsigned *from = UArray_at(identifiers, i);
        unsigned *to = UArray_at(newIdent, i);
        *to = *from;
    }   

    /* Free previous array and return new array */
    UArray_free(&identifiers);
    return newIdent; 
}  

void seg_instr_length(Mem_Seq m, unsigned l) 
{
    m->instr_length = l;
}