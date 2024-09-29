#include "kernel.h"


void print_program(prgm *program){
    printf("PID: %i\n", program->pid);
    printf("Base: %i\n", program->base);
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
    FILE * file1 = fopen("program", "r");
    FILE * file2 = fopen("program2", "r");

    if(file1 == NULL || file2 == NULL){
        puts("File read failure\n");
        exit(EXIT_FAILURE);
    }

    int p2 = allocate_program(10000, NULL, file2, &free_list, &prgm_list);
    int p1 = allocate_program(10000, NULL, file1, &free_list, &prgm_list);

    if(p1 == 0 || p2 == 0){
        puts("Allocation failed\n");
        exit(1);
    }

    schedule_init();
    draw_lottery();

    execution_loop();

}   

void execution_loop(){ // forever loop deals with executing active programs and context switching

    PLE = running_prgm->base + running_prgm->code_base; // physical line of execution
    double time_spent;
    clock_t tick = clock(); // time track for context switching
    clock_t tock;
    int ticks = 0;

    while(true){
        unsigned int opcode = 0; 
        for(int j = 0; j < 4; j++){
            opcode |= (ram[PLE + j] << ((j * 8)));
        }

        if(opcode == 0){
            display_registers();
            program_list_delete(running_prgm, &prgm_list); // delete finished program 

            if(prgm_list == NULL){ // if no more programs exit
                tock = clock();
                time_spent = (double)(tock-tick) / CLOCKS_PER_SEC;
                printf("%f\n", time_spent);
                exit(0);
            }

            draw_lottery();
            tick = clock();

            PLE = regs[RPC] + running_prgm->base+running_prgm->code_base;

            continue;
        }

        
        execute_instruction(opcode);
        PLE = regs[RPC] + running_prgm->base+running_prgm->code_base;
    }
}