#include "jacklib.h"

int strlength(char * s){ // returns the length of a string
    int len = 0;
    for(;;len++){
        if(s[len] == '\0')
            break;
    }
    return len;
}

int power(int base, int p){ // calculates bast to the power of p
    int total = 0;

    if(p == 0)
        return 1;

    if(p == 1)
        return base;

    total = base;
    for(int i = 0; i < p-1; i++){
        total *= base;
    }
    return total;
}

void *substring(char * str, char* dst, int from, int to){
    int j = 0;
    for(int i = from; i < to; i ++){
        dst[j++] = str[i];
    }
    dst[j] = '\0';
}