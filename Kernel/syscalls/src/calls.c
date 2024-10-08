#include "calls.h"

bool waiting_for_input = false;
bool stdin_updated = false;

int (*sysapi[CALL_COUNT])(void) = {
    _read,
    _write,
    _open,
    _close,
    _kill,
    _sleep,
    _exit_prgm,
    _set_window

};

bool valid_address(int address, int size){
    if(address == 0 || address+size > running_prgm->size){ // check valid write addr
        return false; 
    }
    return true;
}

int handle_syscall(int call){
    if(call <= 0 || call > CALL_COUNT)
        return 0;
    sysapi[call-1]();
}

int _read(){ // FIXME 
    int read_addr = regs[REK]; // address to buffer/file being read (later might be a file descriptor)
    int write_address = regs[RJO]; // where to store what is being read (realitive to virtual address space and will be translated)
    int size = regs[R9]; // how much to read

    int bytes_read = 0;

    if(read_addr == 0){ // check valid read addr
        return -1; 
    }

    if(!valid_address(write_address, size)){ // check valid write addr
        return -1; 
    }

    if(size <= 0)
        return -1;


    int physical_read_addr = read_addr + running_prgm->base;
    int physical_write_addr = write_address + running_prgm->base;

    if(read_addr == running_prgm->stdin_base){ // handling stdin
        /* when scheduler is done:
            check if stdin buffer has data
            if not: call a wait and tell scheduler to deschedule current program
            when user hits enter reschedule the program and fill the buffer
            then return contents of buffer to program

            later I want to support multiple windows so the os also has to check the currently open program.  
        */
        char in;
        while (bytes_read < (size-1)) {
            in = getchar();
            if (in == '\n' || in == EOF)
                break;
    
            // Write input from user char by char to stdin 
            if(write_address < regs[RSP])
                ram[physical_write_addr+ bytes_read] = in; // heap grows down
            else
                ram[physical_write_addr - bytes_read] = in; // stack grows up
                
            bytes_read++;
        }
        if(write_address < regs[RSP])
            ram[physical_write_addr + bytes_read] = 0;
        else
            ram[physical_write_addr - bytes_read] = 0;

    }
    
    else{
        // handle file later may implement file descriptors 
    }

    return bytes_read; 
}

int _write(){
    int read_addr = regs[REK];
    int write_addr = regs[RJO];
    int write_size = regs[R9];

    int bytes_written = 0;

    if(!valid_address(write_addr, write_size) || read_addr == 0 || write_size == 0) // check inputs are valid
        return -1;
    
    int physical_read_addr = running_prgm->base + read_addr;
    int physical_write_addr = running_prgm->base + write_addr;

    int to_write = 0;
    for(int i = 0; i < write_size; i++){
        // the way information is written or read depends on if it is the stack or the heap because they grow in opposite directions
        if(read_addr < regs[RSP])
            to_write = ram[physical_read_addr + bytes_written]; // read data by tracing down ram
        else
            to_write = ram[physical_read_addr - bytes_written]; // read data by tracing up ram

        if(to_write == 0) // handle terminating character
            break;

        if(write_addr == running_prgm->stdout_base){
            printf("%c", to_write); // display contents from memory to screen if STDOUD is write address
        }
        else{ // write to memory
            if(write_addr < regs[RSP]){ // if more than stack it is heap
                ram[physical_write_addr + bytes_written] = to_write;
                running_prgm->heap_size++; // increment heap size
            }
            else{
                ram[physical_write_addr - bytes_written] = to_write; // stack
            }
            
        }
        
        bytes_written++;
        
    }
}

int _open(){

}

int _close(){

}

int _kill(){

}

int _sleep(){

}

int _set_window(){

}

int _exit_prgm(){

}