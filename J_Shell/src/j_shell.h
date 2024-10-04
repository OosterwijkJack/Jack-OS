#include <stdio.h>
#include <jmemory.h>
#include <string.h>
#include <ctype.h>

#define MAX_CMD_SIZE 100
#define ROOT_PATH "../File System/root"

int cur_dir;

void get_input_loop();

void handle_input();

bool is_spaces(char * str);

void run_jano(char *file_name);

void run_jexe(char *file_name);

void run_ls();

void run_shutdown();

void run_cd(char *dir);

void run_kill(char* pid);

void run_rm(char *file);

void run_mkdir(char *dir_name);

void run_ps(char *flag);

void run_clear();

void run_cat(char *file);