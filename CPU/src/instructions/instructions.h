#pragma once
#include <unistd.h>
#include "cpu.h"
#include "calls.h"

#define SPECIAL_RET_NUM 50000

// -----instructions-----
void _add();
void _mul();
void _sub();
void _div();
void _and();
void _or();
void _xor();
void _not();
void _mod(); // modulus operator
void _cmpb(); // cmp byte
void _cmpd(); // cmpl (4 bytes)
void _jeq(); // jmp equals
void _jlt(); // jump less than
void _jgt(); // jump greater than
void _jne(); // jump not equals
void _jmp(); // jump
void _movb(); // move data between registers
void _movd();
void _pushb();
void _pushd();
void _pop();
void _int();
void _call();
// -----------------

