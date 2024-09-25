#ifndef SYSCALL_H
#define SYSCALL_H

#include "stdbool.h"
#include "jmemory.h"

#define CALL_COUNT 8

int _read();
int _write();
int _open();
int _close();
int _kill();
int _sleep();
int _set_window();
int _exit();

extern int (*sysapi[CALL_COUNT])(void); // array of syscall functions

int handle_syscall(int call);

#endif /* SYSCALL_H */
