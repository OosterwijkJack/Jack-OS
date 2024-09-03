#pragma once
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "instructions.h"

typedef char byte;

#define INT_S 32
#define REGISTER_COUNT 17
#define INSTRUCTION_COUNT 21
#define INSTRUCTION_SIZE 33 // + 1 for newline
#define PGM_SIZE 1024

extern int regs[REGISTER_COUNT];

#define R0  0
#define R1  1
#define R2  2
#define R3  3
#define R4  4
#define R5  5
#define R6  6
#define R7  7
#define R8  8
#define R9  9
#define RPC 10  // program counter
#define RSP 11  // stack pointer
#define RSB 12  // stack base pointer
#define RFG 13  // flag register
#define RCF 14  // compare flag register
#define RA1 15  // argument 1 reg
#define RA2 16  // argument 2 reg

#define FLAG_ISREG 0 // is register
#define FLAG_ISLITERAL 1 
#define FLAG_CARRY 2
#define FLAG_POS 3
#define FLAG_NEG 4
#define FLAG_ZRO 5 // zero


// array of void pointers that contains methods to handle incoming instructions
extern void(*Instructions[INSTRUCTION_COUNT])(void);

void execute_instruction(int opCode); // binary string to int
int full_adder(void * num1, void *num2);
void load_program(int argc, char*argv[]);



