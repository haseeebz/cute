#include "CuteInstr.h"
#include <sys/types.h>

#include "../exe.h"

#pragma once

typedef struct
{
    Instr instrs[100];
    int pc;
    ExeStack stack;
    int stations[8];
} CuteEngine;


void CuteEngine_init(CuteEngine *engine);
void CuteEngine_run(CuteEngine *engine);
void CuteEngine_end(CuteEngine *engine);