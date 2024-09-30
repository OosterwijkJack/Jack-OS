#pragma once
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "kernel.h"

void threads_init();

// ----Execution Thread----

void start_execution_thread();

typedef struct execution_thread_t{
    bool running;
}execution_thread_t;

extern execution_thread_t *execution_thread;
// ------------------------


// ----TIME THREAD----
#define SLEEP_TIME 1 // 1ms
void *time_thread_void(); // used to keep track of when to schedule a new program
void start_time_thread();

typedef struct time_thread_t{
    bool running;
    double time_since;
    time_t tock;

}time_thread_t;

extern time_thread_t *time_thread;

// -------------------

void kill_threads();