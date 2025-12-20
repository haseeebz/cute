#include "CuteByte.h"

#include "../core/context.h"

#pragma once 

#define CUTE_VERSION "v0.0.3"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
	ctProgramImage img;
} CuteEngine;

extern CuteEngine CtEngine;


// Initializes the Engine
void CuteEngine_init();

// Ends the Engine and all its states
void CuteEngine_end(int exit_code);

// Executes a state struct, the state struct must be properly initialized
void CuteEngine_exec(ctContext *ctx);

// Sets up state struct with function 0 and executes it.
void CuteEngine_run(); 

// Loading an image file
void CuteEngine_loadImage(char *filepath);


#ifdef __cplusplus
}
#endif