#include "memory.h"

prgm *loaded_progams = NULL;
unsigned char ram[RAM_SIZE] = {0};
free_list_t *free_list = NULL;

int cur_pid = 1;

int main(void){
    init_memory();
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
    free_list = new;


}

int allocate_program(int size){
    // [find empy space based on best fit]
    free_list_t *best = NULL;

    for(free_list_t *ptr = best->next; ptr != NULL; ptr = ptr->next){
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

    new_program->next = loaded_progams;
    loaded_progams = new_program; // prepend

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
    free_list_t *new_free = malloc(sizeof(free_list_t));
    new_free->base = new_program->size + new_program->base;
    new_free->size = free_block_size - size;
    new_free->next = free_list;
    free_list = new_free;

}

void find_empy_space(int size){

}

void print_memory(){
    int c = 0;
    for(free_list_t *ptr = free_list; ptr != NULL;ptr=ptr->next){
        printf("\n\nFree block %i:\n", c++);
        printf("Base: %i\n", ptr->base);
        printf("Bound: %i\n",ptr->size+ptr->base);
        printf("Size: %i\n", ptr->size);
    }
}