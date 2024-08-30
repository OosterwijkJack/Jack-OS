#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define RAM_SIZE 20000000 // 20mb

#define NO_MEMORY 0

int cur_pid;

typedef struct prgm{
    int base; // where program starts in physical memory
    int size; // size the program occupies
    int pid; // program id
    struct prgm *next;
}prgm;

typedef struct free_list_t{
    int size;
    int base;
    struct free_list_t *next;
}free_list_t;

extern prgm *loaded_progams; // linked list
free_list_t *free_list;
extern unsigned char ram[RAM_SIZE];

void init_memory();

// allocate using segmentation and return the pid
int allocate_program(int size);

// re allocate programs to reduce external fragmentation
void reallocate_memory_space();

void find_empy_space(int size);

void print_memory();
