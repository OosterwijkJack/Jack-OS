#pragma once
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "instructions.h"
#include "jacklib.h"

typedef unsigned char byte;

#define REGISTER_COUNT 16
#define INSTRUCTION_COUNT 22
#define INSTRUCTION_SIZE 33 // + 1 for newline

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
#define RA1 14  // argument 1 reg
#define RA2 15  // argument 2 reg

#define FLAG_ISREG 0
#define FLAG_ISLITERAL 1
#define FLAG_CARRY 2



// array of void pointers that contains methods to handle incoming instructions
extern void(*Instructions[INSTRUCTION_COUNT])(void);

void init();
void receive_instruction(char opCode_s[INSTRUCTION_SIZE]);
unsigned int binarys_to_int(char * s, size_t size); // binary string to int



