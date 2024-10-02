#include "schedule.h"

prgm * running_prgm = NULL;
int ticket_count = 0;

void schedule_init(){
    srand(time(NULL)); // set rand seed
    running_prgm = prgm_list;

    if(running_prgm != NULL)
        regs[RSP] = running_prgm->size; // set stack pointer
}

int draw_lottery(){
    assign_tickets(); // assign tickets to programs

    if(ticket_count == 0){
        printf("No tickets assigned\n");
        return -1;
    }

    int winning_ticket = rand() % ticket_count; // gen num up to ticket count (exclusive)

    int counter = 0;
    for(prgm *ptr = prgm_list; ptr!=NULL; ptr=ptr->next){ // traverse prgm list

        if(ptr->state == STATE_PAUSED)
            continue;
        counter += ptr->ticket; // add ticket to counter

        if(counter > winning_ticket){// if counter exceeds winning prgm wins
        
            if(switch_program(ptr) != ptr->pid){
                printf("Schedule failure\n");
                exit(EXIT_FAILURE);
            }
            time_thread->tock = clock(); // reset timer    
            return ptr->pid; 
        } 
            
    }   
    return -1;
}

int assign_tickets(){
    int prgm_count = 0;
    ticket_count = 0;

    if(prgm_list == NULL)
        return -1;

    for(prgm *ptr = prgm_list; ptr != NULL; ptr=ptr->next){ // assign tickets based on priority

        if(ptr->state == STATE_PAUSED)
            continue;

        if(ptr->priority == 0){
            ticket_count += P_LOW;
            ptr->ticket = ticket_count;
        }
        else if(ptr->priority == 1){
            ticket_count += P_MED;
            ptr->ticket = ticket_count;
        }
        else{
            ticket_count += P_HIGH;
            ptr->ticket = ticket_count;
        }
        
    }

}

int change_prgm_state(int state){
    if(running_prgm == NULL)
        return -1;
    
    if(state > 2 || state < 0) // invalid state
        return -1;

    running_prgm->state = state;
    return state;
}

int switch_program(prgm *new_prgm){ // schedule new program
    if(new_prgm == NULL)
        return -1;

    // set new program as running
    if(running_prgm != NULL)
        running_prgm->state = STATE_READY; // assign ready state to override running state
    running_prgm = new_prgm;
    for(int i = 0; i < REGISTER_COUNT; i ++){ // save value of programs registers
        running_prgm->save_regs[i] = regs[i];
        regs[i] = new_prgm->save_regs[i]; // set register values to new program
    }

    if(regs[RSP] == 0) // set stack pointer for new programs
        regs[RSP] = new_prgm->size;

    new_prgm->state = STATE_RUNNING;
    return new_prgm->pid;
}