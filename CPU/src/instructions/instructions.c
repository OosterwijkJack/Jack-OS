#include "instructions.h"

void _mov() {
    write(STDOUT_FILENO, "mov\n", sizeof("mov\n") - 1);
    if(regs[RFG] == FLAG_ISLITERAL)
        regs[regs[RA2]] = regs[RA1];
    else
        regs[regs[RA2]] = regs[regs[RA1]];
}

void _add() { // full adder
    write(STDOUT_FILENO, "add\n", sizeof("add\n") - 1);

    unsigned int num1;
    unsigned int num2 = regs[regs[RA2]];
    
    int INT_S = sizeof(int) *8;
    if(regs[RFG] == FLAG_ISLITERAL)
        num1 = regs[RA1];
    else
        num1 = regs[regs[RA1]];

    int carry = 0;
    for(int i = 0 ; i < INT_S; i ++){ // loop for every bit in an intiger

        if(carry){
            num2 ^= (1 << i); // bitwise flip operation on bit mask at location
            if(num2 << i == 0) // check if the flip flipped a 1 bit
                carry = 1; // if it did enable carry
            else
                carry = 0; 
        }
        if(((num1 < i) & 0x1) & ((num2 < i) & 0x1)){ // if both bits are one 
            carry = 1; // enable carry
            num2 ^= (1 >> i); // flip
        }
        else if((((num1 < i) & 0x1) | ((num2 < i) & 0x1))){ // if one of the bits are 1
            num2 |= (1 << i); // set bit to one
        }
    }
    if(carry){
        regs[RFG] = FLAG_CARRY;
    }
}

void _sub() {
    write(STDOUT_FILENO, "sub\n", sizeof("sub\n") - 1);
}

void _mul() {
    write(STDOUT_FILENO, "mul\n", sizeof("mul\n") - 1);
}

void _div() {
    write(STDOUT_FILENO, "div\n", sizeof("div\n") - 1);
}

void _and() {
    write(STDOUT_FILENO, "and\n", sizeof("and\n") - 1);
}

void _or() {
    write(STDOUT_FILENO, "or\n", sizeof("or\n") - 1);
}

void _xor() {
    write(STDOUT_FILENO, "xor\n", sizeof("xor\n") - 1);
}

void _not() {
    write(STDOUT_FILENO, "not\n", sizeof("not\n") - 1);
}

void _compb() {
    write(STDOUT_FILENO, "compb\n", sizeof("compb\n") - 1);
}

void _compl() {
    write(STDOUT_FILENO, "compl\n", sizeof("compl\n") - 1);
}

void _compq() {
    write(STDOUT_FILENO, "compq\n", sizeof("compq\n") - 1);
}

void _jeq() {
    write(STDOUT_FILENO, "jeq\n", sizeof("jeq\n") - 1);
}

void _jlt() {
    write(STDOUT_FILENO, "jlt\n", sizeof("jlt\n") - 1);
}

void _jgt() {
    write(STDOUT_FILENO, "jgt\n", sizeof("jgt\n") - 1);
}

void _jne() {
    write(STDOUT_FILENO, "jne\n", sizeof("jne\n") - 1);
}

void _jmp() {
    write(STDOUT_FILENO, "jmp\n", sizeof("jmp\n") - 1);
}

void _load() {
    write(STDOUT_FILENO, "load\n", sizeof("load\n") - 1);
}

void _save() {
    write(STDOUT_FILENO, "save\n", sizeof("save\n") - 1);
}

void _lea() {
    write(STDOUT_FILENO, "lea\n", sizeof("lea\n") - 1);
}

void _push() {
    write(STDOUT_FILENO, "push\n", sizeof("push\n") - 1);
}

void _pop() {
    write(STDOUT_FILENO, "pop\n", sizeof("pop\n") - 1);
}