#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define STDIN_BASE 1
#define STDIN_SIZE 500


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
    int screen_size; // screen size
    int code_base; // program base within segment
    int code_size; // program size
    int heap_base; // where is heap
    int heap_size; 
    int stack_size; // stack is always at bottom of program
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

extern unsigned char ram[RAM_SIZE];
extern unsigned char swp[SWP_SIZE]; // swap space 

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
int write_memory(int base, int max, FILE* mem);

prgm * get_program(int pid, prgm * w_prgm_list);
void print_memory();