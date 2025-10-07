#include <stdint.h>
#include "../instr.h"
#include "../frame.h"

#pragma once 


 
typedef struct
{
	int pc;
	OpCode* codes;

	ExecutionStack* exestack;

	char* filepath;
} CuteEngine;


CuteEngine* CuteEngine_setup(char* filepath);
void CuteEngine_end(CuteEngine* engine);

void CuteEngine_load(CuteEngine* engine);
void CuteEngine_run(CuteEngine* engine);

void CuteEngine_write(CuteEngine* engine, OpCode* code, int count);







