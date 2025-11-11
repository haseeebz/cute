#include "CuteByte.h"
#include "../context/context.h"

#pragma once 


#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	ctProgramImage img;
} CuteEngine;

extern CuteEngine ctEngine;


void CuteEngine_init();
void CuteEngine_end();
void CuteEngine_loadImage(char* filepath);

CtContext* CuteEngine_newContext();
void CuteEngine_endContext(CtContext** ctx);

void CuteEngine_runMain();
void CuteEngine_execLoop(CtContext* ctx);






#ifdef __cplusplus
}
#endif