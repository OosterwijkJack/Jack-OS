#include "kernel.h"

void print_program(prgm *program){
    printf("PID: %i\n", program->pid);
    printf("stdin base: %i\n", program->stdin_base);
    printf("stdin bound: %i\n", program->stdin_base + STDIN_SIZE);
    printf("stdout base: %i\n", program->stdout_base);
    printf("stdout bound: %i\n", program->stdout_base + STDOUT_SIZE);
    printf("screen base: %i\n", program->screen_base);
    printf("screen bound: %i\n", program->screen_base+program->screen_size);
    printf("code base: %i\n", program->code_base);
    printf("code bound: %i\n", program->code_base + program->code_size);
    printf("heap base: %i\n", program->heap_base);
    printf("heap bound: %i\n", program->heap_base + program->heap_size);
    printf("stack base: %i\n", program->size);
    printf("stack bound: %i\n", program->size-program->stack_size);
}

int main(void){
    init_memory();

    FILE * file = fopen("program", "r");

    if(file == NULL){
        puts("File read failure\n");
        exit(EXIT_FAILURE);
    }

    int p1 = allocate_program(50000, NULL, file, &free_list, &prgm_list);

    if(p1 == 0){
        puts("Allocation failed\n");
        exit(1);
    }

    schedule_init();

    regs[RSP] = running_prgm->size; // set stack pointer

    for(int i = running_prgm->base+running_prgm->code_base; i < running_prgm->base+running_prgm->code_base+running_prgm->code_base; i+=4){
        unsigned int opcode = 0; 
        for(int j = 0; j < 4; j++){
            opcode |= (ram[i + j] << ((j * 8)));
        }
        if(opcode == 0)
            break;
        
        execute_instruction(opcode);
    }
    display_registers();

}   