#include "cpu.h"

// initializ registers to zero
int regs[REGISTER_COUNT] = {0};
int program_memory[(int)PGM_SIZE/4] = {0};

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

    load_program(argc, argv);
    execute_program();
    
    display_registers();
}

void load_program(int argc, char* argv[]){
    char buf[INT_S+2];

    if(argc != 2){
        printf("Usage: ./cpu {file}\n");
        exit(EXIT_FAILURE);
    }

    FILE * fptr = fopen(argv[1], "r");

    if(fptr == NULL){
        printf("Invalid file\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    while(fgets(buf, sizeof(buf), fptr)){
        buf[strcspn(buf, "\n")] = '\0';

        if(strlen(buf) != 32){
            printf("Invalid instruction length at line %i. Cant load program.", count);
            exit(1);
        }

        program_memory[count++] = binarys_to_int(buf, INT_S);
    }
}

void execute_program(){
    while(program_memory[regs[RPC]] != 0){ // run until no more instructions to run

    
        // reset argument registers
        regs[RA1] = 0;
        regs[RA2] = 0;

        unsigned int opCode = program_memory[regs[RPC]]; // instruction at PC
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

        if (arg2 > REGISTER_COUNT+1){
            printf("Invalid register by arg 2\n");
            return;
        }

        if(arg2 != 0){
            regs[RA2] = arg2-1;
        }
            

        //printf("reg1: %i\n", regs[RA1]);
        //printf("reg2: %i\n", regs[RA2]);

        regs[RPC] += 1; // increment program counter
        Instructions[instructionType](); // execute instruction
    }
}

int binarys_to_int(char * s, size_t size){
    int total = 0;
    for(int i = 0; i < size; i ++){ 
        if(s[size - 1 -i] == '1')
            total += (1 << i);
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

