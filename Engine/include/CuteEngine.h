#include <sys/types.h>


#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "CuteByte.h"
#include "../exe/stack.h"



typedef struct
{
    ctProgramImage img;

	size_t pc;
    ExeStack stack;
} CuteEngine;


void CuteEngine_init(CuteEngine *engine);
void CuteEngine_loadImage(CuteEngine *engine, char* filepath);
void CuteEngine_run(CuteEngine *engine, char* filepath);
void CuteEngine_end(CuteEngine *engine);

#ifdef __cplusplus
}
#endif