#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "global.h" // prgm and free list stored here
#include "schedule.h"

extern int cur_pid;
extern unsigned char ram[RAM_SIZE];
extern unsigned char swp[SWP_SIZE]; // swap space 

void init_memory();

// allocate using segmentation and best fit, returns the pid
int allocate_program(int size, int* pid, FILE* prgmCode, free_list_t **w_free_list, prgm **w_prgm_list);
int deallocate_program(int pid, prgm **w_prgm_list, free_list_t **w_free_list, char *mem);
void merge_free_nodes(free_list_t **w_free_list); // merge concurrent free nodes called every deallocation
// reallocate programs to reduce external fragmentation
int reallocate_memory_space();

// translate virtual address to physical address
int translate_address(int pid, int vaddress);

int free_list_prepend(int base, int size, free_list_t **w_free_list);
int free_list_delete(free_list_t * node, bool *merge, free_list_t **w_free_list);

int program_list_prepend(int base, int size, int *pid, prgm **w_prgm_list);
int program_list_delete(prgm* node, prgm **w_prgm_list);

int zero_memory(int base, int bound, char *mem);
int binarys_to_int(char * s, size_t size);
int write_memory(int base, int max, FILE* mem);

prgm * get_program(int pid, prgm * w_prgm_list);
void print_memory();

#endif /* MEMORY_MANAGEMENT_H */
