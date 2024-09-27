#pragma once
#include <time.h>
#include "jmemory.h"
#include "schedule.h"
#include "calls.h"
#include "cpu.h"

#define TIME_SLICE 0.005 // 5 ms

void execution_loop();