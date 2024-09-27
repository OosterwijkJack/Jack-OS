#pragma once

#include "global.h"

void schedule_init();

int switch_program(prgm *new_prgm); // schedules new program

int change_prgm_state(int state); // change between state: paused, ready, running

int assign_tickets(); // assign tickets for lottery draw through priority and randomness

prgm *draw_lotter(); // returns winning program