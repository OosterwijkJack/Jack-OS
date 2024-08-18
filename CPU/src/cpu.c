#include "cpu.h"

// initializ registers to zero
int regs[REGISTER_COUNT] = {0};

// instructions can easily be indexed based on opcode
void(*Instructions[INSTRUCTION_COUNT])(void) = {
    _add,
    _sub,
    _mul,
    _div,
    _and,
    _or,
    _xor,
    _not,
    _compb,
    _compl,
    _compq,
    _jeq,
    _jlt,
    _jgt,
    _jne,
    _jmp,
    _load,
    _save,
    _mov,
    _lea,
    _push,
    _pop
};

int main(void){
    char * a = "101110";
    int b = binarys_to_int(a, strlength(a));
    printf("%i\n", b);
}

void receive_instruction(char instruction[INSTRUCTION_SIZE]){

}

int binarys_to_int(char * s, size_t size){
    int total = 0;
    int c = 0;
    for(int i = size-1; i >= 0; i--){ // loop from end of string backwards 
        if(s[i] == '1') 
            total += power(2, c);
        c+=1;
    }
    return total;
}
