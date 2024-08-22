#include "cpu.h"

// initializ registers to zero
int regs[REGISTER_COUNT] = {0};

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
    _compb,
    _compl,
    _jeq,
    _jlt,
    _jgt,
    _jne,
    _jmp,
    _load,
    _save,
    _lea,
    _push,
    _pop
};

void display_registers(){
    printf("\n");
    for(int i = 0; i < REGISTER_COUNT; i++){
        printf("%i: %i\n",i, regs[i]);
    }
    exit(0);
}

int main(int argc, char* argv[]){
    signal(SIGINT, display_registers);

    if(argc > 1){
        for(int i = 1; i < argc; i ++)
            receive_instruction(argv[i]);
        display_registers();
    }
    else{
        while(1){
            char Opcode_s[INSTRUCTION_SIZE];
            scanf("%s",Opcode_s );
            receive_instruction(Opcode_s);
        }
        
    }

}

void receive_instruction(char opCode_s[INSTRUCTION_SIZE]){

    int len = strlength(opCode_s);

    if(len != 32){
        puts("Invalid instruction length must be 32 bits");
        return;
    }

    // reset argument registers
    regs[RA1] = 0;
    regs[RA2] = 0;

    unsigned int opCode = binarys_to_int(opCode_s, len);
    // get instruction type/function
    unsigned int instructionType = (opCode >> 27) & 0x3f; // 0x3f = 111111 (six 1 bits)
    unsigned int isLiteral = (opCode>>26) & 0x1;// 1
    unsigned int arg1 = (opCode>>10) & 0xffff; // 1111111111111111
    unsigned int arg2 = (opCode >> 5) & 0x1f; // 11111

    if((isLiteral != 0 && arg1 > REGISTER_COUNT) || arg2 > REGISTER_COUNT){
        printf("Invalid register\n");
        return;
    }

    if(instructionType > INSTRUCTION_COUNT){
        printf("Invalid instruction\n");
        return;
    }
    
    if(arg1 != 0){
        if(isLiteral != 0){
            regs[RA1] = arg1;
            regs[RFG] = FLAG_ISLITERAL; // set flag register so instruction knows wether to use value or register
        }
        else{
            regs[RA1] = regs[arg1-1]; // instruction 0 = null so decrement by one (1 = R0) in context of instructions
            regs[RFG] = FLAG_ISREG;
        }
    }

    if(arg2 != 0){
        printf("%i\n", arg2-1);
        regs[RA2] = regs[arg2-1];
    }
        

    printf("reg1: %i\n", regs[RA1]);
    printf("reg2: %i\n", regs[RA2]);

    Instructions[instructionType](); // execute instruction
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

/*
Unused because would hurt performace. I wanted to create the cpu with as many bitwise operations as possible
to try and keep the simulator feeling very authentic

int full_adder(void * num1, void *num2){

    int *n1 = (int * )num1;
    int *n2 = (int * )num2;
    int carry = 0;
    for(int i = 0 ; i < INT_S; i ++){ // loop for every bit in an intiger
        int bit1 = (*n1 >> i) & 0x1;
        int bit2 = (*n2 >> i) & 0x1;

        // Calculate the sum for this bit
        int sum = bit1 ^ bit2 ^ carry;

        // Update the result in num2
        if (sum)
            *n2 |= (1 << i);  // Set the bit to 1
        else
            *n2 &= ~(1 << i);  // Set the bit to 0

        // Update the carry
        carry = (bit1 & bit2) | (carry & (bit1 ^ bit2));
    }
    if(carry){
        regs[RFG] = FLAG_CARRY;
    }   
}
*/

