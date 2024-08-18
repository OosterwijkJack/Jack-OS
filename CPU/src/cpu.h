#pragma once
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "instructions.h"

#define REGISTER_COUNT 14
#define INSTRUCTION_COUNT 25
#define INSTRUCTION_SIZE 33 // + 1 for newline

extern int regs[REGISTER_COUNT];
// array of void pointers that contains methods to handle incoming instructions
extern void(*Instructions[INSTRUCTION_COUNT])(void);

void receive_instruction(char instruction[INSTRUCTION_SIZE]);
int binarys_to_int(char * s, size_t size); // binary string to int



