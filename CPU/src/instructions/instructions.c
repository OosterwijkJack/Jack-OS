#include "instructions.h"


int get_comp_flag(int out){

    if(out == 0)
        return FLAG_ZRO;
    else if(out > 0)
        return FLAG_POS;
    else    
        return FLAG_NEG;
 
}

int get_num1(bool is_dword){
    int num1 = 0;
    // if derefrence
    if(regs[RFG1] == FLAG_ISADDR_REG1){ // pull value from memory register is pointing to
        if(is_dword){
            int address = running_prgm->base + regs[RA1];
            for(int i = address; i < address+4;i++){
                num1 |= (ram[i] << 8*(i-address));
            }
        }
        else{
            num1 = ram[running_prgm->base+regs[RA1]];
        }
    }
    else
        num1 = regs[RA1]; // else pull value from register
    return num1;
}

void _movb() { // move byte
    if(regs[RFG1] == FLAG_ISLITERAL)
        regs[regs[RA2]] = (regs[RA1]&0xff);
    else if(regs[RFG1] == FLAG_ISADDR_LITERAL || regs[RFG1] == FLAG_ISADDR_REG1){
        regs[regs[RA2]] = ram[running_prgm->base+regs[RA1]];
    }
    else
        regs[regs[RA2]] = regs[regs[RA1]]&0xff;
}

// fix this. cant move dword into memory can only read dword
void _movd(){ // move dword (4 bytes)
    if(regs[RFG1] == FLAG_ISLITERAL)
        regs[regs[RA2]] = (regs[RA1]);
    else if(regs[RFG1] == FLAG_ISADDR_LITERAL || regs[RFG1] == FLAG_ISADDR_REG1){
        // collect bytes
        char buf[4];
        for(int i = 0; i < 4; i++){
            if(regs[RFG1] == FLAG_ISADDR_LITERAL)
                buf[i] = ram[running_prgm->base+regs[RA1]+i];
            else
                buf[i] = ram[running_prgm->base+regs[RA1]+i];
        }
        int bytes = 0;
        merge_bytes(buf, 4, &bytes); // make bytes into dword

        regs[regs[RA2]] = bytes; // set register
    }
    else
        regs[regs[RA2]] = regs[RA1];
}

void _add() { 
    int num1 = get_num1(false);

    regs[regs[RA2]] += num1; // add to value of register
}

void _mul(){

    int num1 = get_num1(false);

    regs[regs[RA2]] *= num1; // add to value of register
}
    

void _sub(){

    int num1 = get_num1(false);
    
    regs[regs[RA2]] -= num1; // add to value of register
}

void _div(){
    int num1 = get_num1(false);

    int reg_value = (int)regs[regs[RA2]]/num1;

    regs[regs[RA2]] = reg_value; // add to value of register
}


void _and() {
    
    int num1 = get_num1(false);
    regs[regs[RA2]] &= num1; // add to value of register
}

void _or() {

    int num1 = get_num1(false);

    regs[regs[RA2]] |= num1; // add to value of register
}

void _xor() {

    int num1 = get_num1(false);

    regs[regs[RA2]] ^= num1;
}

void _not() {

    int num1 = get_num1(false);
    regs[regs[RA1]] = ~num1;
}

void _mod(){
    int num1 = get_num1(false);
    regs[regs[RA2]] %= num1;
}

void _cmpb() {

    byte num1 = (byte)get_num1(false);
    byte num2;

    if(regs[RFG2] == FLAG_ISADDR_REG2)
        num2 = ram[running_prgm->base+regs[regs[RA2]]];
    else
        num2 = (byte)regs[regs[RA2]];

    // subtracts num2 from num1
    regs[RCF] = get_comp_flag(num1-num2);

}

void _cmpd() {
    int num1 = (int)get_num1(true);
    int num2 = 0;

    if(regs[RFG2] == FLAG_ISADDR_REG2){ // if dereferenced
        int address = running_prgm->base + regs[regs[RA2]];
        for(int i = address; i < address+4;i++){
            num2 |= (ram[i] << 8*(i-address)); // merge bytes
        }
    }
    else
        num2 = (int)regs[regs[RA2]];

    // subtracts num2 from num1
    regs[RCF] = get_comp_flag(num1-num2);
}

void _jeq() {

    if(regs[RCF] == FLAG_ZRO)
        regs[RPC] = (regs[RA1])*sizeof(int);

}

void _jlt() {

    if(regs[RCF] == FLAG_NEG) // num2 - num1 will be negative if num2 is less than 
        regs[RPC] = (regs[RA1]) * sizeof(int);
    
}

void _jgt() {

    if(regs[RCF] == FLAG_POS)
        regs[RPC] = (regs[RA1])*sizeof(int);
}

void _jne() {

    if(regs[RCF] != FLAG_ZRO)
        regs[RPC] = (regs[RA1])*sizeof(int);
}

void _jmp() {
    regs[RPC] = (regs[RA1])*sizeof(int);
}

void _pushb(){ // push to stack
    int num = regs[RA1];
    // assumes stack is properly managed by user
    ram[running_prgm->base+regs[RSP]] = (char)(num & 0xff);
    
}
void _pushd(){ // push to stack
    int num = regs[RA1];

// assumes stack is properly managed by user
    char buf[4];
    split_bytes((void*)&num,4,buf);
    
    for(int i = 0; i < 4; i ++){
        ram[running_prgm->base+regs[RSP]+i] = buf[i]; 
    }
    

}


void _pop(){ // pop from top of stack
    
}

void _int(){
    int rc = sysapi[regs[RA1]]();
}