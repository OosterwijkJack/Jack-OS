#include "kernel.h"

int main(void){ // init everything

    init_memory();

    threads_init(); // must init threads first because draw lottery needs

    schedule_init();
    draw_lottery(); // assign program

    start_time_thread(); 

    //void (*loop)(void);

    //loop = (void(*)(void)) execution_loop;
    //loop()

    start_execution_thread(); // forever loop that executes active programs

    get_input_loop();    
}   

void *execution_loop(){ // forever loop deals with executing active programs and context switching
 // physical line of execution

    // Rethink this
    while(execution_thread->running){

        while(running_prgm == NULL){ // dont do anything when there is no programs
            // Make this into a bool func that only returns true if a ready program exists. 
            if(prgm_list != NULL){ // if there is a program attempt to schedule it 
                draw_lottery();
                continue;
            }

            usleep(1000);
            continue;
        }
        PLE = regs[RPC] + running_prgm->base + running_prgm->code_base;
        unsigned int opcode = 0; 
        for(int j = 0; j < 4; j++){
            opcode |= (ram[PLE + j] << ((j * 8)));
        }

        if(opcode == 0){
            //display_registers();
            program_list_delete(running_prgm, &prgm_list); // delete finished program 
            running_prgm = NULL;

            if(prgm_list == NULL) // if no more programs exit
                continue;
            
            draw_lottery();

            PLE = regs[RPC] + running_prgm->base+running_prgm->code_base;
            continue;
        }

        execute_instruction(opcode);

        if(time_thread->time_since >= TIME_SLICE){
            draw_lottery();
        }

    }
}

void shutdown(){
    kill_threads();
}