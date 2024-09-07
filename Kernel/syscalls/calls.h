#pragma once
#include "stdbool.h"

#define CALL_COUNT 4

bool waiting_for_input; // be true when waiting for a stdin request. lets sceduler know to not run program
bool stdin_updated; // set to true when stdin buffer has been written so os nows program can now continue

extern void(*sysapi[CALL_COUNT])(void); // array of syscall functions
 