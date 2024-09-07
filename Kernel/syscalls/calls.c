#include "calls.h"

bool waiting_for_input = false;
bool stdin_updated = false;

void (*sysapi[CALL_COUNT])(void) = {

};