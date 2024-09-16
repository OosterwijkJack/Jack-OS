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

void _movb() { // move byte
    if(regs[RFG] == FLAG_ISLITERAL)
        regs[regs[RA2]] = (regs[RA1]&0xff);
    else if(regs[RFG] == FLAG_ISADDR_LITERAL){
        regs[regs[RA2]] = ram[running_prgm->base+regs[RA1]];
    }
    else if(regs[RFG] == FLAG_ISADDR_REG){
        regs[regs[RA2]] = ram[running_prgm->base + regs[regs[RA1]]];
    }
    else
        regs[regs[RA2]] = regs[regs[RA1]]&0xff;
}

void _movd(){ // move dword (4 bytes)
    if(regs[RFG] == FLAG_ISLITERAL)
        regs[regs[RA2]] = (regs[RA1]);
    else if(regs[RFG] == FLAG_ISADDR_LITERAL || regs[RFG] == FLAG_ISADDR_REG){
        // collect bytes
        char buf[4];
        for(int i = 0; i < 4; i++){
            if(regs[RFG] == FLAG_ISADDR_LITERAL)
                buf[i] = ram[running_prgm->base+regs[RA1]+i];
            else
                buf[i] = ram[running_prgm->base+regs[regs[RA1]]+i];
        }
        int bytes = 0;
        merge_bytes(buf, 4, &bytes); // make bytes into dword

        regs[regs[RA2]] = bytes; // set register
    }
    else
        regs[regs[RA2]] = regs[RA1];
}

void _add() { 

    int num1 = regs[RA1];
    int num2 = (regs[regs[RA2]]);
    
    regs[regs[RA2]] += num1;
}

void _mul(){

    int num1 = regs[RA1];
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] *= num1;
    
}
void _sub(){

    int num1 = regs[RA1];
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] -= num1;
}
void _div(){
    int num1 = regs[RA1];
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] /= num1;
}

void _and() {
    
    int num1 = regs[RA1];
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] = num1 & num2;
}

void _or() {

    int num1 = regs[RA1];
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] = num1 | num2;
}

void _xor() {

    int num1 = regs[RA1];
    int num2 = regs[regs[RA2]];

    regs[regs[RA2]] = num1 ^ num2;
}

void _not() {

    int num1 = regs[RA1];
    regs[RA1] = ~num1;
}

void _cmpb() {

    byte num1 = (byte)regs[RA1];
    byte num2 = (byte)regs[regs[RA2]];

    // subtracts num2 from num1
    regs[RCF] = get_comp_flag(num1-num2);

}

void _cmpl() {
    int num1 = (int)regs[RA1];
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

void _push(){ // push to stack
    int num = regs[RA1];
    int n_bytes = regs[RA2];

    // assumes stack is properly managed by user
    if(n_bytes > 1){
        char buf[n_bytes];
        split_bytes((void*)&num,n_bytes,buf);
        
        for(int i = 0; i < n_bytes; i ++){
            ram[running_prgm->base+regs[RSP]+i] = buf[i]; 
        }
    }
    else{
        ram[running_prgm->base+regs[RSP]] = (char)(num & 0xff);
    }
}

void _pop(){ // pop from top of stack
    
}

void _int(){
    write(STDOUT_FILENO, "int\n", 4);

    int rc = sysapi[regs[RA1]]();
}