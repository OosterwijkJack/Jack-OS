#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define RAM_SIZE 20000000 // 20mb
#define SWP_SIZE 30000000 // 30mb

#define ISFREE 0
#define ISPRGM 1

#define NO_MEMORY 0

int cur_pid;

// doubly linked lists
typedef struct prgm{
    int base; // where program starts in physical memory
    int size; // size the program occupies
    int pid; // program id
    struct prgm *next;
    struct prgm *prev;
}prgm;

typedef struct free_list_t{ 
    int size;
    int base;
    struct free_list_t *next;
    struct free_list_t *prev;
}free_list_t;

extern prgm *prgm_list; // linked list
free_list_t *free_list;

extern prgm *swp_prgm_list;
free_list_t *swp_free_list;

extern char ram[RAM_SIZE];
extern char swp[SWP_SIZE]; // swap space 

void init_memory();

// allocate using segmentation and best fit, returns the pid
int allocate_program(int size, int* pid, FILE* prgmCode, free_list_t **w_free_list, prgm **w_prgm_list);
int deallocate_program(int pid, prgm **w_prgm_list, free_list_t **w_free_list, char *mem);
void merge_free_nodes(free_list_t **w_free_list); // merger concurrent free nodes called every deallocation
// re allocate programs to reduce external fragmentation
int reallocate_memory_space();

// translate virtual address to physical address
int translate_address(int pid, int vaddress);

int free_list_prepend(int base, int size, free_list_t **w_free_list);
int free_list_delete(free_list_t * node, bool *merge, free_list_t **w_free_list);

int program_list_prepend(int base, int size, int *pid, prgm **w_prgm_list);
int program_list_delete(prgm* node,prgm **w_prgm_list);

int zero_memory(int base, int bound, char *mem);
int binarys_to_int(char * s, size_t size);
int write_memory(int base, int bound, FILE* mem);

void print_memory();