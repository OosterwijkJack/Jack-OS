#pragma once
#include <stdio.h>
#include <jmemory.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define CMD_SIZE 100
#define ARGS_SIZE 3
#define PATH_SIZE 200

#define ROOT_PATH "/home/jack/Desktop/Jack-OS/File_System/root"

extern char cur_path[PATH_SIZE];

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

void run_jasm(char *in, char *out);