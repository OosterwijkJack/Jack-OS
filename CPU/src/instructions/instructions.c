#include "instructions.h"

int get_reg1(){ // get eithher value of register based on arg1 or arg1
    int num1;
    if(regs[RFG] == FLAG_ISLITERAL){
        num1 = regs[RA1];
    }
    else{
        num1 = regs[regs[RA1]];
    }
    return num1;
}

int get_comp_flag(int out){

    if(out == 0)
        return FLAG_ZRO;
    else if(out > 0)
        return FLAG_POS;
    else    
        return FLAG_NEG;
 
}

void _mov() {
    write(STDOUT_FILENO, "mov\n", sizeof("mov\n") - 1);
    if(regs[RFG] == FLAG_ISLITERAL)
        regs[regs[RA2]] = regs[RA1];
    else
        regs[regs[RA2]] = regs[regs[RA1]];
}

void _add() { // full adder
    write(STDOUT_FILENO, "add\n", sizeof("add\n") - 1);

    int num1 = get_reg1();
    int num2 = (regs[regs[RA2]]);
    
    regs[regs[RA2]] += num1;
}

void _mul(){
    write(STDOUT_FILENO, "mul\n", sizeof("add\n") - 1);

    int num1 = get_reg1();
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] *= num1;
    
}
void _sub(){
    write(STDOUT_FILENO, "sub\n", sizeof("add\n") - 1);

    int num1 = get_reg1();
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] -= num1;
}
void _div(){

}

void _and() {
    write(STDOUT_FILENO, "and\n", sizeof("and\n") - 1);
    
    int num1 = get_reg1();
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] = num1 & num2;
}

void _or() {
    write(STDOUT_FILENO, "or\n", sizeof("or\n") - 1);

    int num1 = get_reg1();
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] = num1 | num2;
}

void _xor() {
    write(STDOUT_FILENO, "xor\n", sizeof("xor\n") - 1);

    int num1 = get_reg1();
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] = num1 ^ num2;
}

void _not() {
    write(STDOUT_FILENO, "not\n", sizeof("not\n") - 1);

    int num1 = regs[RA1];
    regs[RA1] = ~num1;
}

void _compb() {
    write(STDOUT_FILENO, "compb\n", sizeof("compb\n") - 1);

    byte num1 = (byte)get_reg1();
    byte num2 = (byte)regs[regs[RA2]];

    // subtracts num2 from num1
    regs[RFG] = get_comp_flag(num1-num2);

}

void _compl() {
    write(STDOUT_FILENO, "compl\n", sizeof("compl\n") - 1);
    int num1 = (int)get_reg1();
    int num2 = (int)regs[regs[RA2]];

    // subtracts num2 from num1
    regs[RFG] = get_comp_flag(num1-num2);
}

void _jeq() {
    write(STDOUT_FILENO, "jeq\n", sizeof("jeq\n") - 1);

    if(regs[RFG] == FLAG_ZRO)
        regs[RPC] = regs[RA1];

}

void _jlt() {
    write(STDOUT_FILENO, "jlt\n", sizeof("jlt\n") - 1);

    if(regs[RFG] == FLAG_NEG) // num2 - num1 will be negative if num2 is less than 
        regs[RPC] = regs[RA1];
    
}

void _jgt() {
    write(STDOUT_FILENO, "jgt\n", sizeof("jgt\n") - 1);

    if(regs[RFG] == FLAG_POS)
        regs[RPC] = regs[RA1];
}

void _jne() {
    write(STDOUT_FILENO, "jne\n", sizeof("jne\n") - 1);

    if(regs[RFG] != FLAG_NEG)
        regs[RPC] = regs[RA1];
}

void _jmp() {
    write(STDOUT_FILENO, "jmp\n", sizeof("jmp\n") - 1);
    regs[RPC] = regs[RA1];
}

// cant write until i implement memory and stack
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