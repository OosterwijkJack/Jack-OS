#include "kernel.h"

double time_since;
bool time_thread_run;

void *time_thread(){
    time_t tock = clock();
    while(time_thread_run){
        time_since = (double)(tock-clock()) / CLOCKS_PER_SEC;
    }
}

void schedule_time_thread(){

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
                time_thread_run = false;
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