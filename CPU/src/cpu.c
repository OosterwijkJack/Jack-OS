#include "cpu.h"

// initializ registers to zero
int regs[REGISTER_COUNT] = {0};
char program_memory[PGM_SIZE] = {0};

// instructions can easily be indexed based on opcode
void(*Instructions[INSTRUCTION_COUNT])(void) = {
    _add,
    _sub,
    _mul,
    _div,
    _mov,
    _and,
    _or,
    _xor,
    _not,
    _cmpl,
    _cmpb,
    _jeq,
    _jlt,
    _jgt,
    _jne,
    _jmp,
    _load,
    _save,
    _lea,
    _push,
    _pop,
    _int
};

void display_registers(){
    printf("\n");
    for(int i = 0; i < REGISTER_COUNT; i++){
        printf("%i: %i\n",i, regs[i]);
    }
    exit(0);
}


void execute_instruction(unsigned int opCode){
    // reset argument registers
    regs[RA1] = 0;
    regs[RA2] = 0;


    // get instruction type/function
    unsigned int instructionType = (opCode >> 27) & 0x3f; // 0x3f = 111111 (six 1 bits)
    unsigned int isLiteral = (opCode>>26) & 0x1;// 1
    unsigned int arg1 = (opCode>>5) & 0x1fffff; // 1111111111111111
    unsigned int arg2 = (opCode) & 0x1f; // 11111

    if((isLiteral == 0 && arg1 > REGISTER_COUNT) || arg2 > REGISTER_COUNT){
        printf("Invalid register\n");
        return;
    }

    if(instructionType > INSTRUCTION_COUNT){
        printf("Invalid instruction\n");
        return;
    }

    if(isLiteral != 0){
        regs[RA1] = arg1;
        regs[RFG] = FLAG_ISLITERAL; // set flag register so instruction knows wether to use value or register
    }
    else{
        regs[RA1] = regs[arg1-1]; // instruction 0 = null so decrement by one (1 = R0) in context of instructions
        regs[RFG] = FLAG_ISREG;
    }

    if (arg2 > REGISTER_COUNT+1){
        printf("Invalid register by arg 2\n");
        return;
    }

    if(arg2 != 0){
        regs[RA2] = arg2-1;
    }
        

    //printf("reg1: %i\n", regs[RA1]);
    //printf("reg2: %i\n", regs[RA2]);

    regs[RPC] += 4; // increment program counter
    Instructions[instructionType](); // execute instruction
}


