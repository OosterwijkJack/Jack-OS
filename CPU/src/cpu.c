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
    char opCode[INSTRUCTION_SIZE] = {'\0'};
    scanf("%s", opCode);
    receive_instruction(opCode);

}

void receive_instruction(char instruction[INSTRUCTION_SIZE]){
    // get instruction type/function
    char instTypeBits[6];
    substring(instruction,instTypeBits, 0,5); // note: substring is (inclusive, exclusive)
    int instType = binarys_to_int(instTypeBits, strlength(instTypeBits));

    // check if it is valid
    if(instType > INSTRUCTION_COUNT-1){
        puts("Instruction out of range");
        return;
    }
    printf("Instruction type: %i\n", instType);

    // get bit that determines if user wants to use a literal number or a register
    // literal numbers have 16 to work with registers the same (even though they would only 4) for simplicity
    char isLiteralBit[2];
    substring(instruction, isLiteralBit, 5,6);

    char arg1Bits[17];
    substring(instruction, arg1Bits,6,22);
    int arg1 = binarys_to_int(arg1Bits, strlength(arg1Bits));

    // if literal is selected 
    if(isLiteralBit[0] == '1'){
        regs[RA1] = arg1; // register arg1 contains the number
    }
    // if register is selected
    else{
        if(arg1 < REGISTER_COUNT-1){
            putsf("Invalid Register: %i", arg1);
            return;
        }
        regs[RA1] = regs[arg1]; // value of register is placed in arg1

    }

    // second argument is always a register (if there is a second argument)    
    char arg2RegBits[6];
    substring(instruction, arg2RegBits, 22,27);
    int arg2 = binarys_to_int(arg2RegBits, strlength(arg2RegBits));

    if(arg2 > REGISTER_COUNT-1){
        putsf("Invalid Register: %i", arg2);
        return;
    }
    regs[RA2] = regs[arg2];

    // finally call instruction function 
    Instructions[instType]();
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
