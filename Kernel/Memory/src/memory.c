#include "memory.h"

/*

Memory allocation for kernel
note: base is inclusive bound is exclusive 

*/

prgm *program_list = NULL;
unsigned char ram[RAM_SIZE] = {0};
free_list_t *free_list_head = NULL;
free_list_t *free_list_tail = NULL;

int cur_pid = 1;

int main(void){
    init_memory();
    
    int p1 = allocate_program(100);
    int p2 = allocate_program(100);
    int p3 = allocate_program(100);

    deallocate_program(p3);
    deallocate_program(p2);
    deallocate_program(p1);

    print_memory();
}


void init_memory(){
    // initiate free list as the entire region
    free_list_t *new = malloc(sizeof(free_list));

    if(new == NULL){
        printf("Init memory malloc fail\n");
        exit(EXIT_FAILURE);
    }

    new->base = 0;
    new->size = RAM_SIZE;
    new->next = free_list;
    new->prev = free_list;
    free_list = new;


}

int allocate_program(int size){
    // [find empy space based on best fit]
    free_list_t *best = NULL;

    for(free_list_t *ptr = free_list; ptr != NULL; ptr = ptr->next){
        if(best == NULL && ptr->size >= size){
            best = ptr;
            continue;
        }

        if(ptr->size >= size && ptr->size < best->size) // find the smallest space that is big enough 
            best = ptr;
    }

    if(best == NULL)
        return NO_MEMORY;


    // [add program to program list]
    prgm *new_program = malloc(sizeof(prgm));

    if(new_program == NULL){
        printf("new program malloc fail\n");
        exit(EXIT_FAILURE);
    }

    new_program->base = best->base;
    new_program->size = size;
    new_program->pid = cur_pid++;

    new_program->next = program_list;
    program_list = new_program; // prepend

    // [update the free list]
    int free_block_size = best->size;

    // remove block from free list
    if (best == free_list){
        free_list_t *tmp = free_list;
        free_list = free_list->next;
        free(tmp);
    }
    else{

        for(free_list_t *ptr = free_list; ptr != NULL; ptr=ptr->next){

            if(ptr->next == best){
                ptr->next = ptr->next->next;
                free(best);
                break;
            }
        }
    }

    // add new smaller block to free list
    if(new_program->size != free_block_size){ // avoid creating free block of size 0
        free_list_t *new_free = malloc(sizeof(free_list_t));
        new_free->base = new_program->size + new_program->base;
        new_free->size = free_block_size - size;
        new_free->next = free_list;
        free_list = new_free;

    }
    
    return new_program->pid;

}

int deallocate_program(int pid){
    prgm *program = NULL;
    for(prgm  *ptr = program_list; ptr != NULL; ptr=ptr->next){
        if(ptr->pid == pid){
            program = ptr;
            break;
        }
    }
    
    // pid not found
    if(program == NULL)
        return 0; // not success

    
    // add back into free space list
    free_list_t *new_free = malloc(sizeof(free_list_t));

    if(new_free == NULL){
        printf("Deallocate free space malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_free->base = program->base;
    new_free->size = program->size;
    new_free->next = free_list;
    free_list = new_free;    

    // [free node]
    if(program == program_list){
        prgm *tmp = program_list;
        program_list = program_list->next;
        free(tmp);
    }
    
    else{
        for(prgm *ptr = program_list; ptr != NULL; ptr=ptr->next){

            if(ptr->next == program){
                ptr->next = ptr->next->next;
                free(program);
                break;
            }
        }
    }

    merge_free_nodes(); // check if any free nodes can be merged
    return 1; // success
}

void merge_free_nodes(){

    // free nodes that have neighbouring node with the same base as nodes bound
     if((free_list->base + free_list->size) == free_list->next->base){
        free_list_t *tmp = free_list;
        free_list = free_list->next;

        free_list->size += tmp->size; // add size
        free_list->base = tmp->base; // merge base

        free(tmp);

    }   
    for(free_list_t *ptr = free_list; ptr->next != NULL; ptr=ptr->next){
        // if base == bound
        if(ptr->base + ptr->size == (ptr->next->base)){
            free_list_t *tmp = ptr->next;
            ptr->next = ptr->next->next;

            ptr->next->next->size += tmp->size;
            ptr->next->next->base = tmp->base;

            free(ptr->next);
        }
    }
}

void free_list_append(int size, int base){
    // check if head
    if(free_list_tail == NULL){
        
    }

}
void free_list_delete(free_list_t * node){

}

void print_memory(){
    int c = 0;
    free_list_t list[25];

    printf("FREE LIST:");
    for(free_list_t *ptr = free_list; ptr != NULL;ptr=ptr->next){
        printf("\n\nFree block %i:\n", c++);
        printf("Base: %i\n", ptr->base);
        printf("Bound: %i\n",ptr->size+ptr->base);
        printf("Size: %i\n", ptr->size);
    }
    printf("\nPROGRAM LIST:");
    for(prgm *ptr = program_list; ptr != NULL;ptr=ptr->next){
        printf("\n\nPid %i:\n", ptr->pid);
        printf("Base: %i\n", ptr->base);
        printf("Bound: %i\n",ptr->size+ptr->base);
        printf("Size: %i\n", ptr->size);
    }
}