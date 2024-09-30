#include "kernel.h"

int main(void){ // init everything

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

    threads_init(); // must init threads first because draw lottery needs

    schedule_init();
    draw_lottery(); // assign program

    start_time_thread(); 
    start_execution_thread(); // forever loop that executes active programs

    while(1){
        usleep(1000);
    }
}   

void *execution_loop(){ // forever loop deals with executing active programs and context switching

    PLE = running_prgm->base + running_prgm->code_base; // physical line of execution

    while(execution_thread->running){
        unsigned int opcode = 0; 
        for(int j = 0; j < 4; j++){
            opcode |= (ram[PLE + j] << ((j * 8)));
        }

        if(opcode == 0){
            display_registers();
            program_list_delete(running_prgm, &prgm_list); // delete finished program 

            while(prgm_list == NULL){ // if no more programs exit
                usleep(1000); // wait until there is a program to execute
            }

            draw_lottery();

            PLE = regs[RPC] + running_prgm->base+running_prgm->code_base;
            continue;
        }

        execute_instruction(opcode);

        if(time_thread->time_since >= TIME_SLICE){
            draw_lottery();
        }

        PLE = regs[RPC] + running_prgm->base+running_prgm->code_base;
    }
}

void shutdown(){
    kill_threads();
}