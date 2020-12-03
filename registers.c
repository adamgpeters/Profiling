/****************************************************************************
 *  COMP 40 HW6 Universal Machine                                           *
 *                                                                          *
 *  registers.c                                                             *
 *  Complete Registers Array Implementation                                 *
 *  Created By (UTLN): jlai03 & apeter09                                    *
 *           On      : 11/22/2020                                           *
 *                                                                          *
 ****************************************************************************/

#include "registers.h"

/************************ CONSTRUCTOR / DESTRUCTOR ***************************/
Reg_arr Reg_new(int num_reg) 
{
    // return UArray_new(num_reg, sizeof(uint32_t));
    
    Reg_arr r = malloc(sizeof(uint32_t) * num_reg);
    for(int i = 0 ; i < num_reg; i ++) {
        r[i] = 0;
    }
    return r;
}

void Reg_free(Reg_arr *r) 
{
    // UArray_free(r);
    free(*r);
}

/**************************** GETTER / SETTER ********************************/
uint32_t Reg_get(Reg_arr r, int index) 
{
    // assert(r!= NULL && index >= 0);
    return r[index];
} 

uint32_t Reg_set(Reg_arr r, int index, uint32_t val) 
{
    // assert(r != NULL && index >= 0);
    r[index] = val;
    return val;
}
