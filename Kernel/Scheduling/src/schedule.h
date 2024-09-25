#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "global.h"

void schedule_init();

void pause_current_program();
int switch_program(prgm *new_prgm);

#endif /* SCHEDULE_H */
