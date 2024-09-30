#pragma once

#include "global.h"
#include "j_threads.h"
#include <stdlib.h>
#include <time.h>

#define P_LOW 100
#define P_MED 300
#define P_HIGH 1000

void schedule_init();

int switch_program(prgm *new_prgm); // schedules new program

int change_prgm_state(int state); // change between state: paused, ready, running

int assign_tickets(); // assign tickets for lottery draw through priority and randomness

int draw_lottery(); // returns winning program