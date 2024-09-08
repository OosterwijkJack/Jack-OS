#include "schedule.h"

prgm * running_prgm = NULL;

void schedule_init(){
    running_prgm = prgm_list;
}