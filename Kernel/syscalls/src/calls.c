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
    _create_window

};

int handle_syscall(int call){
    if(call <= 0 || call > CALL_COUNT)
        return 0;
    sysapi[call-1]();
}

int _read(){
    int read_addr = regs[R9]; // address to buffer/file being read (later might be a file descriptor)
    int write_address = regs[R8]; // where to store what is being read (realitive to virtual address space and will be translated)
    int size = regs[R7]; // how much to read

    if(read_addr == 0 || !(read_addr >= running_prgm->code_base && read_addr <= (running_prgm->code_base + running_prgm->code_size))){
        return 0; 
    }

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

int _create_window(){

}