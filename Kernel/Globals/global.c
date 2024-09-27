#include "global.h"

prgm *prgm_list = NULL;
free_list_t *free_list = NULL;

prgm *swp_prgm_list = NULL;
free_list_t *swp_free_list = NULL;

int PLE = 0;


void split_bytes(void *v_bytes_in, size_t n_bytes, char bytes_out[]){

    unsigned int bytes_in = *((unsigned int *)v_bytes_in);
    for(int i = 0; i < n_bytes; i++){
        bytes_out[i] = (bytes_in >> i*8) & 0xff;
    }
    
}

void merge_bytes(char *bytes_in, size_t n_bytes, unsigned int *out){
    for(int i = 0; i < n_bytes; i++){
        *out |= (bytes_in[i] << (i*8));
    }
}