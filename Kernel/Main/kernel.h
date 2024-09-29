#pragma once
#include <time.h>
#include <unistd.h>
#include "jmemory.h"
#include "schedule.h"
#include "calls.h"
#include "cpu.h"

#define TIME_SLICE 1// 5 ms

void execution_loop();
void *time_thread();