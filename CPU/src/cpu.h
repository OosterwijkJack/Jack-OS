#pragma once
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "instructions.h"
#include "schedule.h"

typedef char byte;

#define INT_S 32
#define REGISTER_COUNT 21
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
#define RFG1 13  // flag register
#define RFG2 14
#define RCF 15  // compare flag register
#define RA1 16  // argument 1 reg
#define RA2 17  // argument 2 reg
#define REK 18
#define RJO 19

#define FLAG_ISREG 0 // is register
#define FLAG_ISLITERAL 1 
#define FLAG_ISADDR_REG1 2
#define FLAG_ISADDR_LITERAL 3
#define FLAG_ISADDR_REG2 4
#define FLAG_CARRY 5
#define FLAG_POS 6
#define FLAG_NEG 7
#define FLAG_ZRO 8 // zero



// array of void pointers that contains methods to handle incoming instructions
extern void(*Instructions[INSTRUCTION_COUNT])(void);

void execute_instruction(unsigned int opCode); // binary string to int
int full_adder(void * num1, void *num2);
void load_program(int argc, char*argv[]);
void display_registers();



