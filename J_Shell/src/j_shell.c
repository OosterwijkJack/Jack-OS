#include "j_shell.h"

char cur_path[PATH_SIZE] = ROOT_PATH;


// splits command by spaces into list 
int split_command(char cmd[CMD_SIZE], char out[ARGS_SIZE][CMD_SIZE]){
    memset(out, 0, sizeof(char)* 2 * CMD_SIZE); // zero out
    char *token;
    const char delimiter[] = " "; // Space is the delimiter

    // Get the first token
    token = strtok(cmd, delimiter);
    if(token != NULL)
        strcpy(out[0], token);
    
    int count = 1;
    while(1){
        
        if(count > ARGS_SIZE){
            printf("Too many arguments\n");
            return -1;
        }

        token = strtok(NULL, delimiter); 

        if(token != NULL)
            strcpy(out[count++], token); 
        else
            break;
        
    }
    
}

void get_input_loop(){
    char buf[CMD_SIZE*ARGS_SIZE];
    char command[ARGS_SIZE][CMD_SIZE];

    while(1){
        

        memset(buf, 0, sizeof(buf)); // zero buf
        printf("JackOS:root%s$ ", cur_path + strlen(ROOT_PATH));
        fgets(buf, CMD_SIZE, stdin);
        
        size_t buf_len = strlen(buf);
        if(buf_len <= 1){ // empty command
            continue;
        }

        if(buf[buf_len-1] == '\n')
            buf[buf_len-1] = '\0'; // remove newwline
        
        if(is_spaces(buf))
            continue;
        
        if(split_command(buf, command) == -1)  // seperate lines
            continue;

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
    else if(strcmp(command[0], "cd") == 0){
        run_cd(command[1]);
    }
    else if(strcmp(command[0], "jano") == 0){
        run_jano(command[1]);
    }
    else if(strcmp(command[0], "cat") == 0){
        run_cat(command[1]);
    } 
    else if(strcmp(command[0], "jasm") == 0){
        run_jasm(command[1], command[2]);
    }  
    else if(strcmp(command[0], "shutdown") == 0){
        run_shutdown();
    }
    else if(strcmp(command[0], "clear") == 0){
        run_clear();
    }
    else{
        printf("command %s not found\n", command[0]);
        sleep(1);
    }
}

void append_cur_path(char* buf, char *name){
    strcat(buf, cur_path);
    strcat(buf, "/");
    strcat(buf, name);

}

void run_jexe(char *file_name){

    char tmp[PATH_SIZE] = {0};
    append_cur_path(tmp, file_name);
    
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

void run_cd(char * dir){
    if(strcmp("..", dir) == 0 && strlen(cur_path) > strlen(ROOT_PATH)){
        int len = strlen(cur_path);
        for(int i = len ; i > 0; i--){

            if(cur_path[i] == '/'){
                cur_path[i] = 0;
                break;
            }

            cur_path[i] = 0;
        }
    }
    else if(strcmp("root", dir) == 0){
        strcpy(cur_path, ROOT_PATH);
    }
    else{
        strcat(cur_path, "/");
        strcat(cur_path, dir);
    }
}

// this might be theft
void run_jano(char *file_name){
    char tmp[PATH_SIZE];
    append_cur_path(tmp, file_name);
    
    pid_t pid = fork();

    if(pid < 0){
        printf("Nano fork failed\n");
        return;
    }
    else if(pid == 0){
        execlp("nano", "nano", tmp, NULL);

        // should not run
        printf("Nano exec failed\n");
        return;
    }
    else{
        wait(NULL);
    }
}

void run_jasm(char *in, char *out){
    pid_t pid = fork();

    char tmp_in[PATH_SIZE] = {0};
    char tmp_out[PATH_SIZE] = {0};

    append_cur_path(tmp_in, in);
    append_cur_path(tmp_out, out);

    if(pid < 0){
        printf("Jasm fork failed\n");
        return;
    }
    else if(pid == 0){
        execlp("jasm", "jasm", tmp_in, tmp_out, NULL);

        printf("Jasm exec failed\n");
        return;
    }
    else{
        wait(NULL);
    }
}

void run_cat(char *file){
    char tmp[PATH_SIZE];
    append_cur_path(tmp, file);
    
    pid_t pid = fork();

    if(pid < 0){
        printf("Cat fork failed\n");
        return;
    }
    else if(pid == 0){
        execlp("cat", "cat", tmp, NULL);

        // should not run
        printf("Cat exec failed\n");
        return;
    }
    else{
        wait(NULL);
    }
}

void run_clear(){
    system("clear");
}

void run_shutdown(){
    kill_threads();

    time_t start, end;
    double elapsed;

    time(&start);

    do{
        system("clear");
        printf("Shutting down system.\n");
        usleep(500 * 1000);
        system("clear");
        printf("Shutting down system..\n");
        usleep(500 * 1000);
        system("clear");
        printf("Shutting down system...\n");
        usleep(500 * 1000);

        time(&end);
        elapsed = (double)(end-start);
    } while(elapsed < 3.0);
    exit(0);
}

bool is_spaces(char * str){ // check if string consists of only spaces
    int len = strlen(str);

    for(int i = 0; i < len; i++){
        if(!(isspace(str[i])))
            return false;
    }
    return true;
}
