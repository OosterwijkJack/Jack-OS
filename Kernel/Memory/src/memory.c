#include "memory.h"

/*

Memory allocation for kernel
note: base is inclusive bound is exclusive 

*/

prgm *loaded_progams = NULL;
unsigned char ram[RAM_SIZE] = {0};
free_list_t *free_list = NULL;

int cur_pid = 1;

int main(void){
    init_memory();
    int p1 = allocate_program(100);
    int p2 = allocate_program(1000);

    deallocate_program(p2);

    int p3 = allocate_program(1000);
    int p4 = allocate_program(5);
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
    for(prgm  *ptr = loaded_progams; ptr != NULL; ptr=ptr->next){
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
    if(program == loaded_progams){
        prgm *tmp = loaded_progams;
        loaded_progams = loaded_progams->next;
        free(tmp);
    }
    
    else{
        for(prgm *ptr = loaded_progams; ptr != NULL; ptr=ptr->next){

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
    for(prgm *ptr = loaded_progams; ptr != NULL;ptr=ptr->next){
        printf("\n\nPid %i:\n", ptr->pid);
        printf("Base: %i\n", ptr->base);
        printf("Bound: %i\n",ptr->size+ptr->base);
        printf("Size: %i\n", ptr->size);
    }
}