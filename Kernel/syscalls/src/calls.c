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
    _set_window

};

int handle_syscall(int call){
    if(call <= 0 || call > CALL_COUNT)
        return 0;
    sysapi[call-1]();
}

int _read(){
    int read_addr = regs[REK]; // address to buffer/file being read (later might be a file descriptor)
    int write_address = regs[RJO]; // where to store what is being read (realitive to virtual address space and will be translated)
    int size = regs[R9]; // how much to read

    int bytes_read = 0;

    if(read_addr == 0){ // check valid read addr
        return -1; 
    }

    if(write_address == 0 || write_address <= running_prgm->code_base || write_address+size > running_prgm->size){ // check valid write addr
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
       while(in=getchar()){
            if(in == '\n')
                break;
            // write input from user char by char
            ram[running_prgm->base+read_addr+bytes_read] = in;
            bytes_read++;

       }
    }
    else{
        // handle file later may implement file descriptors 
    }

    for(int i = 0; i < size; i ++){ // write stdin to write address
        ram[write_address+running_prgm->base+i] = ram[running_prgm->base+read_addr+i];
    }
    ram[running_prgm->base+read_addr+size] = 0; // terminating character
    return bytes_read; 
}

int _write(){

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