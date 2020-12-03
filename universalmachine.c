/****************************************************************************
 *  COMP 40 HW6 Universal Machine                                           *
 *                                                                          *
 *  universalmachine.c                                                      *
 *  Complete Universal Machine Implementation                               *
 *  Created By (UTLN): jlai03 & apeter09                                    *
 *           On      : 11/22/2020                                           *
 *                                                                          *
 *  Contains the implementation for a Universal Machine, which reads and    *
 *  processes .um files. The machine allocates and deallocate memory in a   *
 *  memory sequence and a Register Array. Further, the machine performs     *
 *  various operations on this memory with an Operations CPU.               *
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "operations_cpu.h"
#include "bitpack.h"
#include "array.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define REG_MASK 7
#define MASK_OP 0xF0000000
#define MASK_VAL 0x1FFFFFF
#define MASK_A_VAL 0xE000000


/********************* STRUCT & FUNCTION DECLARATIONS ************************/

/* Universal Machine Opcodes */
typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, MAP, UNMAP, OUT, IN, LOADP, LV
} Um_opcode;

/* Function Declarations */
void read_file(char *filename, Mem_Seq m);
void exec_um(Mem_Seq m, Reg_arr r);
Um_opcode op_type(uint32_t instruction);
void exec_instr(Mem_Seq m, Reg_arr r, cpu cpu, Um_opcode op_type, 
                uint32_t instruction);
void quit_um(Mem_Seq m, Reg_arr r);

/******************* READ FILE FUNCTION **************************************/
/*
  Function:  read_file
  Arguments: char *filename - name of the file to be opened
             Mem_Seq m - Mem_Seq struct to be intialized
  Does:      Intializes first segment of Mem_Seq's memory with enough 
             indices to hold all the instructions to be read in. Opens the 
             specified file, bitpacks each instruction, and stores it into the 
             first segment of the memory sequence. 
  Return:    none - void
*/
void read_file(char *filename, Mem_Seq m)
{
    /* Add Segment with enough indices to hold instructions */
    struct stat* s = malloc(sizeof(*s));
    stat(filename, s);
    unsigned num_words = (s->st_size) / 4; 
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "No such file or directory\n");
        free(s); 
        Mem_free_all(&m);
        exit(EXIT_FAILURE);
    }

    Mem_addseg(m, num_words);

    /* Create instructions word */
    for (unsigned i = 0; i < num_words; i++){
        uint32_t word = 0;
        for (unsigned z = 0; z < 4; z ++) {
            word = Bitpack_newu(word, 8, 24 - z * 8, getc(f));
        }
        
        (((m->memory->seq)[0])->arr)[i] = word;
        // ((Sequence_get(m->memory, 0))->arr)[i] = word;


        
        // Array_put((Array_T)Seq_get(m->memory, 0), i, word);
        // Mem_seg_put(m, 0, i, word);
        // *elem = word;
    }
    /* Free stat pointer and close file */
    free(s); 
    fclose(f);    
}

/******************** UM EXECUTION FUNCTIONS *********************************/
/*
  Function:  exec_um
  Arguments: Mem_Seq m - pointer to Mem_Seq struct 
             Reg_arr r - pointer to Register Array 
             cpu cpu - pointer to cpu struct of functions
  Does:      Uses a program counter to iterate through the instructions 
             stored in the first segment of memory. Each instruction is 
             executed and the overarching data structures are changed 
             accordingly.
  Return:    none - void
*/
void exec_um(Mem_Seq m, Reg_arr r)
{
    int program_counter = 0;



    // int instr_length = Mem_seglength(m, 0);

    


    int instr_length = ((m->memory->seq)[0])->length;
    uint32_t instruction, value;
    unsigned a, b, c; 


    /* Iterate through Instruction Segment */
    while (program_counter < instr_length) {
        /* Parse and Execute Instruction */
        // Array_get((Array_T)Seq_get(m->memory, seg_index), index);
        
        instruction = (((m->memory->seq)[0])->arr)[program_counter];
        
                                // ((Sequence_get(m->memory, 0))->arr)[
                                //                             program_counter];

    

        //  Array_get((Array_T)Seq_get(m->memory, 0), program_counter);
        Um_opcode op = op_type(instruction);
        // op_parse(instruction, &info);
        
        switch (op) {
            case CMOV: 
                c = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                b = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                a = (instruction & REG_MASK); 
                if (r[c] != 0) {
                    r[a] = r[b];
                    // Reg_set(r, a, r[b]);
                }
                break;
            case SLOAD: 
                c = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                b = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                a = (instruction & REG_MASK); 


                r[a] = (((m->memory->seq)[r[b]])->arr)[r[c]];

                // r[a] = (((Array_T)Sequence_get(m->memory, r[b]))->arr)[r[c]];


                break;
            case SSTORE: 
                c = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                b = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                a = (instruction & REG_MASK); 

                (((m->memory->seq)[r[a]])->arr)[r[b]] = r[c];

                // (((Array_T)Sequence_get(m->memory, r[a]))->arr)[r[b]] = r[c];


                break;
            case ADD: 
                c = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                b = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                a = (instruction & REG_MASK); 
                r[a] = r[b]+r[c];
                break;
            case MUL: 
                c = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                b = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                a = (instruction & REG_MASK); 
                r[a] = r[b] * r[c];
                break;
            case DIV: 
                c = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                b = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                a = (instruction & REG_MASK); 
                assert(r[c] != 0);
                r[a] = r[b] / r[c]; 
                break;
            case NAND: 
                c = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                b = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                a = (instruction & REG_MASK); 
                r[a] = ~(r[b] & r[c]);
                break; 
            case HALT: 
                Reg_free(&r);
                Mem_free_all(&m);
                // Free_cpu(&cpu);
                exit(EXIT_SUCCESS);
                break; /* TODO */
            case MAP: 
                c = (instruction & REG_MASK); 
                instruction = instruction >> 3;
                b = (instruction & REG_MASK); 


/********************** ADD SEG INLINE ***************************************/

                // unsigned placement = Mem_addseg(m, length);

                unsigned placement;

                int length = r[c];
                 /* Initialize Segment */
                Array_T seg = Array_new(length);
                if (seg == NULL) {
                    placement = 0;
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

                    placement = (s->size) - 1;
                } else {
                    unsigned seqIndex = Ident_pop(m->identifiers);

                    (m->memory->seq)[seqIndex] = seg;
                    // Sequence_put(m->memory, seqIndex, seg);  
                    placement =  seqIndex;             
                }


/*****************************************************************************/


                /* Ensure that there was enough memory to map a new segment */
                // assert(placement != 0);
                r[b] = placement;
                break;
            case UNMAP: 
                c = (instruction & REG_MASK); 

/********************** FREE SEG INLINE ***************************************/


                // Mem_freeseg(m, r[c]);
                
                int seg_index = r[c];
                
                Array_T seg_temp = (m->memory->seq)[seg_index];
                if (seg_temp != NULL) {
                    /* Push index to Identifiers */
                    if (seg_index != 0) {
                        Ident_push(m->identifiers, seg_index);
                    }
                    /* Free Segment */
                    Array_free(&seg_temp);
                    Sequence_put(m->memory, seg_index, NULL);
                }


/*****************************************************************************/

                break;
            case OUT: 
                c = (instruction & REG_MASK); 
                unsigned num = r[c];
                assert(num <= 255);
                putchar(num);
                break;
            case IN: 
                c = (instruction & REG_MASK); 
                
                // cpu->input(r, c);
                
                int val = getchar();
                assert(val >= 0 && val <= 255);
                if (val == EOF) {
                    r[c] = ~((unsigned)0);
                    // Reg_set(r, c, ~((unsigned)0));
                } else {
                    r[c] = val;
                    // Reg_set(r, c, val);
                }
                
                break;
            case LOADP: 
                b = ((instruction >> 3) & REG_MASK); 
                // cpu->load_program(r, m, b);       
                Mem_load(m,r[b]);
                

                break;
            case LV: 
                value = instruction & MASK_VAL;
                a = (instruction & MASK_A_VAL) >> 25;

                r[a] = value;
                // cpu->load_value(r, a, value);          
                break;
            default: 
                assert(op < 14);
        }

        /* Update Program Counter */
        if (op == LOADP) {
            program_counter = Reg_get(r, (instruction & REG_MASK));

            

            instr_length =((m->memory->seq)[0])->length;
            // instr_length = Mem_seglength(m, 0);
        } else {
            program_counter ++;
        }
    }
    Reg_free(&r);
    Mem_free_all(&m);
    exit(EXIT_SUCCESS);
}

/*
  Function:  op_type
  Arguments: uint32_t instruction - bitpacked 
  Does:      Takes a given (uint32_t) instruction and returns the encoded 
             optype in the bit representation. 
  Return:    none - void
*/
Um_opcode op_type(uint32_t instruction)
{
    return (instruction & MASK_OP) >> 28;
}

/*
  Function:  exec_instr
  Arguments: Mem_seq m - pointer to Mem_Seq struct
  Does:      Takes in a pointer to an instr_info struct and executes the 
             encoded instruction indicated by the struct's optype. Each optype
             aligns with a function which exists in the cpu function struct. 
  Return:    none - void
*/
void exec_instr(Mem_Seq m, Reg_arr r, cpu cpu, Um_opcode op_type, 
                uint32_t instruction)
{
    unsigned a, b, c; 
    uint32_t value;
    switch (op_type) {
        case CMOV: 
            c = (instruction & REG_MASK); 
            instruction = instruction >> 3;
            b = (instruction & REG_MASK); 
            a = (instruction >> 3 & REG_MASK); 
            cpu->move(r, a, b, c);     
            break;
        case SLOAD: 
            c = (instruction & REG_MASK); 
            instruction = instruction >> 3;
            b = (instruction & REG_MASK); 
            a = (instruction >> 3 & REG_MASK); 
            cpu->load(r, m, a, b, c);     
            break;
        case SSTORE: 
            c = (instruction & REG_MASK); 
            instruction = instruction >> 3;
            b = (instruction & REG_MASK); 
            a = (instruction >> 3 & REG_MASK); 
            cpu->store(r, m, a, b, c);   
            break;
        case ADD: 
            c = (instruction & REG_MASK); 
            instruction = instruction >> 3;
            b = (instruction & REG_MASK); 
            a = (instruction >> 3 & REG_MASK); 
            cpu->add(r, a, b, c);           
            break;
        case MUL: 
            c = (instruction & REG_MASK); 
            instruction = instruction >> 3;
            b = (instruction & REG_MASK); 
            a = (instruction >> 3 & REG_MASK); 
            cpu->mult(r, a, b, c);          
            break;
        case DIV: 
            c = (instruction & REG_MASK); 
            instruction = instruction >> 3;
            b = (instruction & REG_MASK); 
            a = (instruction >> 3 & REG_MASK); 
            cpu->divide(r, a, b, c);        
            break;
        case NAND: 
            c = (instruction & REG_MASK); 
            instruction = instruction >> 3;
            b = (instruction & REG_MASK); 
            a = (instruction >> 3 & REG_MASK); 
            cpu->nand(r, a, b, c);         
            break; 
        case HALT: 
            cpu->halt(r, m, cpu);                            
            break; /* TODO */
        case MAP: 
            c = (instruction & REG_MASK); 
            b = (instruction >> 3 & REG_MASK); 
            cpu->map(r, m, b, c);                 
            break;
        case UNMAP: 
            c = (instruction & REG_MASK); 
            cpu->unmap(r, m, c);                      
            break;
        case OUT: 
            c = (instruction & REG_MASK); 
            cpu->output(r, c);                  
            break;
        case IN: 
            c = (instruction & REG_MASK); 
            cpu->input(r, c);                    
            break;
        case LOADP: 
            b = ((instruction >> 3) & REG_MASK); 
            cpu->load_program(r, m, b);               
            break;
        case LV: 
            value = instruction & MASK_VAL;
            a = (instruction & MASK_A_VAL) >> 25;
            cpu->load_value(r, a, value);          
            break;
        default: 
            assert(op_type < 14);
    }
}

/********************* MAIN FUNCTION *****************************************/
int main(int argc, char *argv[]) 
{
    /* Create Memory Sequence, Register Array, and CPU function struct */
    Mem_Seq m = Mem_new(4);
    Reg_arr r = Reg_new(8);
    // cpu cpu = Create_cpu();

    /* Read in File */
    if (argc > 2 ) {
        fprintf(stderr, "Too many files specified.\n");
        exit(EXIT_FAILURE);
    } else if (argc == 2) {
        read_file(argv[1], m);
    } else {
        fprintf(stderr, "No file specified.\n");
        exit(EXIT_FAILURE);
    }

    /* Universal Machine Execution */
    exec_um(m, r);

    return 0;
}
