#pragma once
#include <stdlib.h>
#include <stdbool.h>

// [MEMORY AND PROGRAM RELATED GLOBALS]

//definitions
#define STDIN_BASE 1
#define STDIN_SIZE 512
#define STDOUT_SIZE 512

#define RAM_SIZE 20000000 // 20mb
#define SWP_SIZE 30000000 // 30mb

// types
// doubly linked lists
typedef struct prgm{
    int base; // where program starts in physical memory
    int size; // size the program occupies
    int pid; // program id
    int stdin_base;
    int stdout_base;
    int screen_base;
    int screen_size; // screen size
    int code_base; // program base within segment
    int code_size; // program size
    int heap_base; // where is heap
    int heap_size; 

    int stack_size;

    bool waiting_for_io; 

    struct prgm *next;
    struct prgm *prev;
}prgm;

typedef struct free_list_t{ 
    int size;
    int base;
    struct free_list_t *next;
    struct free_list_t *prev;
}free_list_t;

// vars
extern free_list_t *free_list;
extern prgm *prgm_list;

extern free_list_t *swp_free_list;
extern prgm *swp_prgm_list;

void split_bytes(void *bytes_in, size_t n_bytes, char bytes_out[]); // splits any type into binary array of chars
void merge_bytes(char *bytes_in, size_t n_bytes, unsigned int *out);

extern prgm *running_prgm; 