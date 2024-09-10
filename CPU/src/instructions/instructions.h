#pragma once
#include <unistd.h>
#include "cpu.h"
#include "calls.h"

// -----instructions-----
void _add();
void _mul();
void _sub();
void _div();
void _and();
void _or();
void _xor();
void _not();
void _cmpb(); // cmp byte
void _cmpl(); // cmpl (4 bytes)
void _jeq(); // jmp equals
void _jlt(); // jump less than
void _jgt(); // jump greater than
void _jne(); // jump not equals
void _jmp(); // jump
void _load(); // load data from memore
void _save(); // save data to memory
void _mov(); // move data between registers
void _lea(); // load effective address
void _push(); // push to stack
void _pop(); // pop from stack
void _load(); // load memory to heap
void _hfree(); // free memory from heap
void _int();
// -----------------