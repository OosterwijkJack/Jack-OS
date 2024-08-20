
#include <stdio.h>

int main(void){
    unsigned int num1 = 5;
    unsigned int num2 = 12;
    
    int INT_S = sizeof(int) *8;

    int carry = 0;
    for(int i = 0 ; i < INT_S; i ++){ // loop for every bit in an intiger

        if(carry){
            num2 ^= (1 << i); // bitwise flip operation on bit mask at location
            if(num2 << i == 0) // check if the flip flipped a 1 bit
                carry = 1; // if it did enable carry
            else
                carry = 0; 
        }
        if(((num1 < i) & 0x1) & ((num2 < i) & 0x1)){ // if both bits are one 
            carry = 1; // enable carry
            num2 ^= (1 >> i); // flip
        }
        else if((((num1 < i) & 0x1) | ((num2 < i) & 0x1))){ // if one of the bits are 1
            num2 |= (1 << i); // set bit to one
        }
    }
    if(carry){
        puts("CARRY");
    }   
    printf("%i\n", num2);
    
}

