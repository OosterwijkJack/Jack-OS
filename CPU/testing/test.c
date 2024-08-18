#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void test(){
    puts("A\n");
    return;
}

int main(void){
    void * a = (void*)&test;
    int size = sizeof(a);
    printf("%i\n", size);

    a;
    
}

