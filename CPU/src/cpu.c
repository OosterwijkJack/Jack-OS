#include "cpu.h"

// initializ registers to zero
int regs[REGISTER_COUNT] = {0};

// instructions can easily be indexed based on opcode
void(*Instructions[INSTRUCTION_COUNT])(void) = {
    _add,
    _sub,
    _mul,
    _div,
    _movb,
    _movd,
    _and,
    _or,
    _xor,
    _not,
    _mod,
    _cmpd,
    _cmpb,
    _jeq,
    _jlt,
    _jgt,
    _jne,
    _jmp,
    _pushb,
    _pushd,
    _pop,
    _int
};

void display_registers(){
    printf("\n");
    for(int i = 0; i < REGISTER_COUNT; i++){
        printf("%i: %i\n",i, regs[i]);
    }
}


void execute_instruction(unsigned int opCode){
    // reset argument registers
    double time_spent;
    regs[RA1] = 0;
    regs[RA2] = 0;


    // get instruction type/function
    unsigned int instructionType = (opCode >> 27) & 0x1f; // 0x1f = 11111 (five 1 bits)
    unsigned int arg1_identifier = (opCode>>25) & 0x3;// 1*3
    unsigned int arg1 = (opCode>>6) & 0x7ffff; // 1*19
    unsigned int arg2_identifier = (opCode >> 5) & 0x1;
    unsigned int arg2 = (opCode) & 0x1f; // 1*5


    if(((arg1_identifier == FLAG_ISREG || arg1_identifier == FLAG_ISADDR_REG1) && arg1 > REGISTER_COUNT) || arg2 > REGISTER_COUNT){
        printf("Invalid register\n");
        return;
    }

    if(instructionType > INSTRUCTION_COUNT){
        printf("Invalid instruction\n");
        return;
    }

    // arg1 is always just a value
    if(arg1_identifier == FLAG_ISREG || arg1_identifier == FLAG_ISADDR_REG1 ){
        regs[RA1] = regs[arg1-1]; // instruction 0 = null so decrement by one (1 = R0) in context of instructions
        regs[RFG1] = arg1_identifier;
    }
    else{
        regs[RA1] = arg1;
        regs[RFG1] = arg1_identifier; // set flag register so instruction knows wether to use value or register
    }

    if (arg2 > REGISTER_COUNT+1){
        printf("Invalid register by arg 2\n");
        return;
    }
    // arg2 is usally a register being assigned a value but not always
    if(arg2 != 0 ){
        regs[RA2] = arg2-1;

        if(arg2_identifier)
            regs[RFG2] = FLAG_ISADDR_REG2;
       
    }
    
    //printf("reg1: %i\n", regs[RA1]);
    //printf("reg2: %i\n", regs[RA2]);

    regs[RPC] += 4; // increment program counter
    Instructions[instructionType](); // execute instruction

}

void load_data_section(){

}
