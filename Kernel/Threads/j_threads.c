#include "j_threads.h"

time_thread_t *time_thread = NULL;
execution_thread_t *execution_thread = NULL;


void threads_init(){
    // init execution thread struct
    execution_thread = malloc(sizeof(execution_thread_t));
    execution_thread->running = true;

    // init time thread struct
    time_thread = malloc(sizeof(time_thread_t));
    time_thread->time_since = 0;
    time_thread->running = true;
    time_thread->tock;

    // init locks
    locks = malloc(sizeof(locks_t));
    pthread_mutex_init(&locks->execution_lock, NULL);

    // init conds and cond variables
    conds = malloc(sizeof(cond_t));
    
    pthread_cond_init(&conds->execution_cond,NULL);
    conds->execution_done = 0;
}

void start_execution_thread(){
    pthread_t thread_id;

    if(pthread_create(&thread_id, NULL, execution_loop, NULL)){
        printf("Timer thread failed\n");
        exit(EXIT_FAILURE);
    }
}

void *time_thread_void(){
    time_thread->tock = clock();
    while(time_thread->running){
        time_thread->time_since = (double)(clock()-time_thread->tock) / CLOCKS_PER_SEC;
        usleep(SLEEP_TIME*1000);
    }
}

void start_time_thread(){
    pthread_t thread_id;

    if(pthread_create(&thread_id, NULL, time_thread_void, NULL)){
        printf("Timer thread failed\n");
        exit(EXIT_FAILURE);
    }
}

void kill_threads(){
    time_thread->running = false;
    execution_thread->running = false;
}