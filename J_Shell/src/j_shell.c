#include "j_shell.h"

// splits command by spaces into list 
void split_command(char cmd[MAX_CMD_SIZE], char out[2][MAX_CMD_SIZE]){
    memset(out, 0, sizeof(char)* 2 * MAX_CMD_SIZE); // zero out
    char *token;
    const char delimiter[] = " "; // Space is the delimiter

    // Get the first token
    token = strtok(cmd, delimiter);
    if(token != NULL)
        strcpy(out[0], token);
    token = strtok(NULL, delimiter); 

    if(token != NULL)
        strcpy(out[1], token);
    
}

void get_input_loop(){
    char buf[MAX_CMD_SIZE];
    char command[2][MAX_CMD_SIZE];
    while(1){

        memset(buf, 0, sizeof(buf)); // zero buf
        printf("JackOS:/$ ");
        fgets(buf, MAX_CMD_SIZE, stdin);
        
        size_t buf_len = strlen(buf);
        if(buf_len <= 1){ // empty command
            continue;
        }

        if(buf[buf_len-1] == '\n')
            buf[buf_len-1] = '\0'; // remove newwline
        
        if(is_spaces(buf))
            continue;
        
        split_command(buf, command); // seperate lines
        handle_input(command); // execute command
    }
}

void handle_input(char command[2][MAX_CMD_SIZE]){
    if(strcmp(command[0], "jexe") == 0){
        run_jexe(command[1]);
    }
    else{
        printf("command %s not found\n", command[0]);
        sleep(1);
    }
}

bool is_spaces(char * str){ // check if string consists of only spaces
    int len = strlen(str);

    for(int i = 0; i < len; i++){
        if(!(isspace(str[i])))
            return false;
    }
    return true;
}

void run_jexe(char *file_name){

    FILE * prgm_code = fopen(file_name, "r");

    if(prgm_code == NULL){
        printf("%s not found\n", file_name);
        return;
    }

    // create lock and signal execution thread that there is a new program
    pthread_mutex_lock(&locks->execution_lock);

    int pid = allocate_program(DEFAULT_PRGM_SIZE, NULL, prgm_code, &free_list, &prgm_list); // allocate program to prgm_list

    conds->execution_done = 1;
    pthread_mutex_unlock(&locks->execution_lock);
    pthread_cond_signal(&conds->execution_cond);


    // TO DO: Replace spin loops with thread signiling
    while(get_program(pid, prgm_list)){ // wait for program to finish
        usleep(100 * 1000);
    }

}