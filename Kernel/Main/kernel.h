#pragma once
#include <time.h>
#include <unistd.h>
#include "jmemory.h"
#include "schedule.h"
#include "calls.h"
#include "cpu.h"
#include "j_threads.h"
#include "j_shell.h"

#define TIME_SLICE 0.1// 100 ms

void *execution_loop();