#include "jmemory.h"

/*

Memory allocation for kernel
note: base is inclusive bound is exclusive 

*/

unsigned char ram[RAM_SIZE] = {0};
unsigned char swp[SWP_SIZE] = {0};


int cur_pid = 1;


void init_memory(){
    // initiate free list as the entire region
    free_list_t *new = malloc(sizeof(free_list_t));

    if(new == NULL){
        printf("Init memory malloc fail\n");
        exit(EXIT_FAILURE);
    }

    new->base = 0;
    new->size = RAM_SIZE;
    new->next = NULL;
    new->prev = NULL;
    free_list = new;

    new = malloc(sizeof(free_list_t));

    if(new == NULL){
        printf("Init memory malloc fail\n");
        exit(EXIT_FAILURE);
    }

    new->base = 0;
    new->size = SWP_SIZE;
    new->next = NULL;
    new->prev = NULL;
    swp_free_list = new;

}
                                                            // working list
int allocate_program(int size, int* pid, FILE* prgmCode, free_list_t **w_free_list, prgm **w_prgm_list){ 
    // [find empy space based on best fit]

    free_list_t *best = NULL;

    for(free_list_t *ptr = *w_free_list; ptr != NULL; ptr = ptr->next){

        if(best == NULL && ptr->size >= size){
            best = ptr;
            continue;
        }

        if(ptr->size >= size && ptr->size < best->size) // find the smallest space that is big enough 
            best = ptr;
    }

    if(best == NULL)
        return 0;


    // [add program to program list]

    // prepend program list
    program_list_prepend(best->base, size, pid, w_prgm_list);

    // write program data 
    int data_size = 0;
    if(prgmCode != NULL){
        data_size = write_memory((*w_prgm_list)->base + (*w_prgm_list)->data_base, (*w_prgm_list)->base + size-1,prgmCode); // write program data
    }

    if(data_size == 0){
        return -1;
    }
    // assign bases now that we are aware of data size
    (*w_prgm_list)->data_size = data_size;

    (*w_prgm_list)->screen_base = (*w_prgm_list)->data_base + (*w_prgm_list)->data_size;
    (*w_prgm_list)->screen_size = 500;

    (*w_prgm_list)->code_base = (*w_prgm_list)->screen_base + (*w_prgm_list)->screen_size;
    
    // Write program code into memory block at base + code_base
    int code_size = 0;

    // (base, max, program code)
    code_size = write_memory((*w_prgm_list)->base + (*w_prgm_list)->code_base, (*w_prgm_list)->base + size-1,prgmCode); // write program code
    
    if(code_size == 0){
        // make sure there is code
        printf("Program code empty\n");
        return 0;  
    }  
    
    (*w_prgm_list)->code_size = code_size;
    (*w_prgm_list)->heap_base = (*w_prgm_list)->code_base + code_size;
    
    
    // [update the free list]
    int free_block_size = best->size;

    // remove block from free list
    free_list_delete(best, NULL, w_free_list);

    // add new smaller block to free list
    if((*w_prgm_list)->size != free_block_size){ // avoid creating free block of size 0
        free_list_t *new_free = malloc(sizeof(free_list_t));
        new_free->base = (*w_prgm_list)->size + (*w_prgm_list)->base;
        new_free->size = free_block_size - size;
        new_free->next = *w_free_list;
        *w_free_list = new_free;
    }
    (*w_prgm_list)->state = STATE_READY;
    return (*w_prgm_list)->pid;

}

int deallocate_program(int pid, prgm **w_prgm_list, free_list_t **w_free_list, char *mem){
    // find program from pid
    prgm *program = NULL;
    for(prgm  *ptr = *w_prgm_list; ptr != NULL; ptr=ptr->next){
        if(ptr->pid == pid){
            program = ptr;
            break;
        }
    }
    
    // pid not found
    if(program == NULL)
        return 0; // not success

    
    // add back into free space list
    free_list_prepend(program->base, program->size, w_free_list); 

    zero_memory(program->base, program->base+program->size, mem);
    program_list_delete(program, w_prgm_list);

    merge_free_nodes(w_free_list); // check if any free nodes can be merged

    pthread_mutex_lock(&locks->deallocation_lock);
    conds->deallocation_done = 1;
    pthread_cond_signal(&conds->deallocation_cond);
    pthread_mutex_unlock(&locks->deallocation_lock);

    return 1; // success
}

void merge_free_nodes(free_list_t **w_free_list){

   
    for(free_list_t *ptr = *w_free_list; ptr != NULL;ptr=ptr->next){

        for(free_list_t *ptr2 = *w_free_list; ptr2 != NULL;){

            if(ptr == ptr2){
                ptr2=ptr2->next;
                continue;
            }


            bool merge = false;
            // check below for merge blocks

            // if base == bound
            if(ptr->base + ptr->size == (ptr2->base)){
                free_list_t *tmp = NULL;

                if(ptr2->prev != NULL)
                    tmp = ptr2->prev;
                else
                    tmp=ptr2->next;

                ptr->size += ptr2->size;
                free_list_delete(ptr2, &merge, w_free_list);
                ptr2=tmp;
            }
            else if(ptr2->base + ptr2->size == ptr->base){
                free_list_t *tmp = NULL;

                if(ptr2->prev != NULL)
                    tmp = ptr2->prev;
                else
                    tmp=ptr2->next;

                ptr->size += ptr2->size;
                ptr->base = ptr2->base;

                free_list_delete(ptr2, &merge, w_free_list);
                ptr2 = tmp;
            }
            
            if(!merge)
                ptr2=ptr2->next;
        }
    }
}

int free_list_prepend(int base, int size, free_list_t **w_free_list){
    // check if head
    free_list_t *tmp  = malloc(sizeof(free_list_t));

    if(tmp == NULL){
        printf("Program list prepend malloc fail\n");
        exit(EXIT_FAILURE);
    }


    tmp->size = size;
    tmp->base = base;
    tmp->next = *w_free_list;
    tmp->prev = NULL;

    if(*w_free_list != NULL)
        (*w_free_list)->prev = tmp;
    
    *w_free_list=tmp;
    return 1;

}
int free_list_delete(free_list_t * node, bool *merge, free_list_t **w_free_list){

    if(node == NULL)
        return 0;

    // head
    if(node == *w_free_list){
        *w_free_list = node->next;

        if(*w_free_list != NULL)
            (*w_free_list)->prev = NULL;
    }

    if(node->next != NULL)
        node->next->prev = node->prev;
    if(node->prev != NULL){
        node->prev->next = node->next;
    }
    
    free(node);

    if(merge != NULL)
        *merge = true;

    return 1;
}

int program_list_prepend(int base, int size, int* pid, prgm **w_prgm_list){
    prgm *tmp  = malloc(sizeof(prgm));

    if(tmp == NULL){
        printf("Program list prepend malloc fail\n");
        exit(EXIT_FAILURE);
    }

    tmp->size = size;
    tmp->base = base;

    tmp->stdin_base = 1; // 0 reserved for null

    tmp->stdout_base = STDIN_SIZE + tmp->stdin_base;

    // data hasnt been loaded yet so cant init anything below it 
    tmp->data_base = tmp->stdout_base + STDOUT_SIZE;

    // to init:
    // screen,code,heap

    // stack base is always just the size of the program

    tmp->stack_size = 0;

    tmp->state = STATE_PAUSED;
    tmp->ticket = -1;
    tmp->priority = 1;

    for(int i = 0 ; i < REGISTER_COUNT; i ++){ // set registers to zero
        tmp->save_regs[i] = 0;
    }
    
    // assign new pid if pid is NULL
    if(pid != NULL)
        tmp->pid = *pid;
    else
        tmp->pid = cur_pid++;

    tmp->next = *w_prgm_list;
    tmp->prev = NULL;

    if(*w_prgm_list != NULL)
        (*w_prgm_list)->prev = tmp;
    
    *w_prgm_list=tmp;
    return 1;
}
int program_list_delete(prgm* node,prgm **w_prgm_list){
    if(node == NULL)
        return 0;

    // head
    if(node == *w_prgm_list){
        *w_prgm_list = node->next;

        if(*w_prgm_list != NULL)
            (*w_prgm_list)->prev = NULL;
    }

    if(node->next != NULL)
        node->next->prev = node->prev;
    if(node->prev != NULL){
        node->prev->next = node->next;
    }
    
    free(node);
    return 1;
}

int reallocate_memory_space(){
    // moves all programs to swp space
    for(prgm *ptr = prgm_list; ptr != NULL; ptr=ptr->next){
        // allocate space for program
        if(allocate_program(ptr->size, &ptr->pid, NULL, &swp_free_list, &swp_prgm_list) == 0)
            puts("NO");

        // [then copy program memory to swap space]
        
        //find base and bound in swap memory
        prgm* swpptr = swp_prgm_list; // dont need to search since all programs are prepended
        
        if(swpptr == NULL)
            return 1;

        // copy memory from ram to swap
        for(int i = 0; (i < swpptr->size) && (i < ptr->size);i++){
            swp[swpptr->base + i] = ram[ptr->base+i];
        }
        
        // deallocate program from ram
        deallocate_program(ptr->pid, &prgm_list, &free_list, ram);
    }

    // reallocate every program in swp space back into ram contiguously (same thing as above but reversed)
    for(prgm *swpptr = swp_prgm_list; swpptr!=NULL; swpptr=swpptr->next){
        allocate_program(swpptr->size, &swpptr->pid, NULL, &free_list, &prgm_list);

        prgm *prgmptr = prgm_list;

        if(prgmptr == NULL)
            return 1;
        
        for(int i = 0;(i < prgmptr->size) && (i < swpptr->size);i++){
            ram[prgmptr->base+i] = swp[swpptr->base+i];
        }

        deallocate_program(swpptr->pid, &swp_prgm_list, &swp_free_list, swp);
    }
    return 0;
}

int zero_memory(int base, int bound, char * mem){
    if(base < 0 || bound > RAM_SIZE)
        return 0;

    for(int i = base; i < bound; i++){
        mem[i] = 0;
    }
    return 1;
}


int write_memory(int base, int max, FILE* mem){
    if(mem == NULL){
        printf("Invalid file\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char buf[INT_S/4+2];
    int size = 0;
    int binary = 0;
    int zero_count = 0;
    for(int i = base; ;  i++){

        if(i >= max){
            printf("Program memory exceeds max\n");
            return 0;
        }
        
        if(!fgets(buf,sizeof(buf), mem))
            break;

        buf[strcspn(buf, "\n")] = '\0';

        if(strlen(buf) != 8){
            printf("Invalid memory length at line %i. Cant load program.", count);
            return 0;
        }
        binary = binarys_to_int(buf, INT_S/4);

        // count zeros
        if(binary == 0)
            zero_count++;
        else
            zero_count = 0;

        if(zero_count >= 4){ // data section terminates with 32 bits of 0
            break;
        }

        ram[i] = binary;
        size++;
    }
    return size;
}

int binarys_to_int(char * s, size_t size){
    int total = 0;
    for(int i = 0; i < size; i ++){ 
        if(s[size - 1 -i] == '1')
            total += (1 << i);
    }
    return total;
}

prgm * get_program(int pid, prgm * w_prgm_list){
    for(prgm * ptr = w_prgm_list; ptr != NULL; ptr=ptr->next){
        if(ptr->pid == pid)
            return ptr;
    }
    return NULL;
}


void print_memory(){
    int c = 0;

    printf("\nFREE LIST:");
    for(free_list_t *ptr = free_list; ptr != NULL;ptr=ptr->next){
        printf("\n\nFree block %i:\n", c++);
        printf("Base: %i\n", ptr->base);
        printf("Bound: %i\n",ptr->size+ptr->base);
        printf("Size: %i\n", ptr->size);
    }
    printf("\nPROGRAM LIST:");
    for(prgm *ptr = prgm_list; ptr != NULL;ptr=ptr->next){
        printf("\n\nPid %i:\n", ptr->pid);
        printf("Base: %i\n", ptr->base);
        printf("Bound: %i\n",ptr->size+ptr->base);
        printf("Size: %i\n", ptr->size);
    }
    printf("\n\n-------------------");
}

