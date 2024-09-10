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
    if(regs[RFG] == FLAG_ISLITERAL)
        regs[regs[RA2]] = regs[RA1];
    else
        regs[regs[RA2]] = regs[regs[RA1]];
}

void _add() { 

    int num1 = get_reg1();
    int num2 = (regs[regs[RA2]]);
    
    regs[regs[RA2]] += num1;
}

void _mul(){

    int num1 = get_reg1();
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] *= num1;
    
}
void _sub(){

    int num1 = get_reg1();
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] -= num1;
}
void _div(){
    int num1 = get_reg1();
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] /= num1;
}

void _and() {
    
    int num1 = get_reg1();
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] = num1 & num2;
}

void _or() {

    int num1 = get_reg1();
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] = num1 | num2;
}

void _xor() {

    int num1 = get_reg1();
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] = num1 ^ num2;
}

void _not() {

    int num1 = regs[RA1];
    regs[RA1] = ~num1;
}

void _cmpb() {

    byte num1 = (byte)get_reg1();
    byte num2 = (byte)regs[regs[RA2]];

    // subtracts num2 from num1
    regs[RCF] = get_comp_flag(num1-num2);

}

void _cmpl() {
    int num1 = (int)get_reg1();
    int num2 = (int)regs[regs[RA2]];

    // subtracts num2 from num1
    regs[RCF] = get_comp_flag(num1-num2);
}

void _jeq() {

    if(regs[RCF] == FLAG_ZRO)
        regs[RPC] = (regs[RA1]-1)*sizeof(int);

}

void _jlt() {

    if(regs[RCF] == FLAG_NEG) // num2 - num1 will be negative if num2 is less than 
        regs[RPC] = (regs[RA1]-1) * sizeof(int);
    
}

void _jgt() {

    if(regs[RCF] == FLAG_POS)
        regs[RPC] = (regs[RA1]-1)*sizeof(int);
}

void _jne() {

    if(regs[RCF] != FLAG_ZRO)
        regs[RPC] = (regs[RA1]-1)*sizeof(int);
}

void _jmp() {
    regs[RPC] = (regs[RA1]-1)*sizeof(int);
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
void _int(){
    write(STDOUT_FILENO, "int\n", 4);

    int rc = sysapi[regs[RA1]]();
}