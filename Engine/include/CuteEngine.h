#include "CuteInstr.h"
#include <sys/types.h>

#pragma once

typedef struct
{
    Instr instrs[100];
    int pc;
} CuteEngine;
