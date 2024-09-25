#pragma once
#include "schedule.h"

prgm * running_prgm = NULL;

void schedule_init(){
    regs[RSP] = running_prgm->size; // set stack pointer
    running_prgm = prgm_list;

}

int switch_program(prgm *new_prgm){ // schedule new program
    if(new_prgm == NULL)
        return -1;

    for(int i = 0; i < REGISTER_COUNT; i ++){ // save value of programs registers
        running_prgm->save_regs[i] = regs[i];
        regs[i] = new_prgm->save_regs[i]; // set register values to new program
    }

    if(regs[RSP] == 0) // set stack pointer for new programs
        regs[RSP] = new_prgm->size;

    new_prgm->instructions_executed = 0; // reset # of instructions executed

    running_prgm = new_prgm;
    return new_prgm->pid;
}