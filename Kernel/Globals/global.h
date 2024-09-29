#ifndef MEMORY_PROGRAM_GLOBALS_H
#define MEMORY_PROGRAM_GLOBALS_H

typedef struct prgm prgm;
typedef struct free_list_t free_list_t;

// [MEMORY AND PROGRAM RELATED GLOBALS]

// definitions
#define STDIN_BASE 1
#define STDIN_SIZE 512
#define STDOUT_SIZE 512

#define RAM_SIZE 20000000 // 20mb
#define SWP_SIZE 30000000 // 30mb

extern int PLE; // Physical line of execution. (Keeps track of what data inside ram will be sent to CPU)

#include <stdlib.h>
#include <stdbool.h>
#include <cpu.h>

#define STATE_RUNNING 0 // program is running
#define STATE_READY 1 // program is ready to run
#define STATE_PAUSED 2 // program is paused (likely for io)


// types
// doubly linked lists
typedef struct prgm {
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
    int save_regs[REGISTER_COUNT];
    struct prgm *next;
    struct prgm *prev;

    int state; // for scheduler
    int ticket; // for lottery
    int priority;
} prgm;

typedef struct free_list_t {
    int size;
    int base;
    struct free_list_t *next;
    struct free_list_t *prev;
} free_list_t;

// vars
extern free_list_t *free_list;
extern prgm *prgm_list;

extern free_list_t *swp_free_list;
extern prgm *swp_prgm_list;

void split_bytes(void *bytes_in, size_t n_bytes, char bytes_out[]); // splits any type into binary array of chars
void merge_bytes(char *bytes_in, size_t n_bytes, unsigned int *out);

extern prgm *running_prgm;

#endif /* MEMORY_PROGRAM_GLOBALS_H */
