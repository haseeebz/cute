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
} ctEngine;

extern ctEngine engine;


// Initializes the Engine
void ctEngine_init();

// Ends the Engine and all its states
void ctEngine_end(int exit_code);

// Executes a state struct, the state struct must be properly initialized
void ctEngine_exec(ctContext *ctx);

// Sets up state struct with function 0 and executes it.
void ctEngine_run(); 

// Loading an image file
void ctEngine_loadImage(char *filepath);


#ifdef __cplusplus
}
#endif