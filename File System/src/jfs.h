#pragma once
#include "stdio.h"
#include <stdlib.h>

void file_system_init();

typedef struct inode{
    int cur_node; // node of current directory
    int *dir_nodes; // list of every file/dir nodes in cur dir
    int parent_node; // parent dir node
}inode;


