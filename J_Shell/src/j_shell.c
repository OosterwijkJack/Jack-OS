#include "j_shell.h"

char cur_path[PATH_SIZE] = ROOT_PATH;

// splits command by spaces into list 
void split_command(char cmd[CMD_SIZE], char out[2][CMD_SIZE]){
    memset(out, 0, sizeof(char)* 2 * CMD_SIZE); // zero out
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
    char buf[CMD_SIZE];
    char command[2][CMD_SIZE];

    while(1){
        

        memset(buf, 0, sizeof(buf)); // zero buf
        printf("JackOS:/$ ");
        fgets(buf, CMD_SIZE, stdin);
        
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

void handle_input(char command[2][CMD_SIZE]){
    if(strcmp(command[0], "jexe") == 0){
        run_jexe(command[1]);
    }
    else if(strcmp(command[0], "ls") == 0){
        run_ls();
    }
    else{
        printf("command %s not found\n", command[0]);
        sleep(1);
    }
}

void run_jexe(char *file_name){

    char tmp[PATH_SIZE] = {0};
    strcat(tmp, cur_path);
    strcat(tmp, "/");
    strcat(tmp, file_name);
    
    FILE * prgm_code = fopen(tmp, "r");

    if(prgm_code == NULL){
        printf("%s not found\n", file_name);
        return;
    }

    // create lock and signal execution thread that there is a new program
    pthread_mutex_lock(&locks->execution_lock);

    int pid = allocate_program(DEFAULT_PRGM_SIZE, NULL, prgm_code, &free_list, &prgm_list); // allocate program to prgm_list

    fclose(prgm_code);

    conds->execution_done = 1;
    pthread_cond_signal(&conds->execution_cond);
    pthread_mutex_unlock(&locks->execution_lock);

    pthread_mutex_lock(&locks->deallocation_lock);
    while(conds->deallocation_done == 0){ // wait for program to finish
        pthread_cond_wait(&conds->deallocation_cond, &locks->deallocation_lock);
    }
    conds->deallocation_done = 0;
    pthread_mutex_unlock(&locks->deallocation_lock);
}

void run_ls(){
    pid_t pid = fork(); // create copy process

    if(pid < 0){
        printf("ls fork failed");
        return;
    }
    else if(pid == 0){ // if child
        execlp("ls", "ls", cur_path, NULL); // execute ls on current path
        printf("ls failed\n");
        return;
        
    }
    else{
        wait(NULL); // wait for child
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
