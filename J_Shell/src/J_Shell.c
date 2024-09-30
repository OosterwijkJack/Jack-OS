#include "J_Shell.h"

void split_command(char cmd[MAX_CMD_SIZE], char out[2][MAX_CMD_SIZE]){
    char *token;
    const char delimiter[] = " "; // Space is the delimiter

    // Get the first token
    token = strtok(cmd, delimiter);
    strcpy(out[0], token);
    token = strtok(NULL, delimiter); 

    if(token != NULL)
        strcpy(out[1], token);
    
}

void input_loop(){
    char buf[MAX_CMD_SIZE];
    while(1){
        scanf("%s", &buf);

        if(strlen(buf) > MAX_CMD_SIZE){
            printf("Command exceeds max\n");
            continue;
        }


    }
}

void run_jexe(char *file_name){

}