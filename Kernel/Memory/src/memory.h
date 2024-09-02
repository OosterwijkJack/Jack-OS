#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define RAM_SIZE 20000000 // 20mb

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

extern prgm *program_list; // linked list
free_list_t *free_list;
extern unsigned char ram[RAM_SIZE];

void init_memory();

// allocate using segmentation and best fit, returns the pid
int allocate_program(int size, int* pid);
int deallocate_program(int pid);
void merge_free_nodes(); // merger concurrent free nodes called every deallocation
// re allocate programs to reduce external fragmentation
void reallocate_memory_space();

// translate virtual address to physical address
int translate_address(int pid, int vaddress);

int free_list_prepend(int base, int size);
int free_list_delete(free_list_t * node, bool *merge);

int program_list_prepend(int base, int size, int pid);
int program_list_delete(prgm* node);

void print_memory();