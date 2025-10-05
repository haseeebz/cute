#include <stdint.h>
#include "../instr.h"
#include "../memory.h"

#pragma once 

#define REG_COUNT 8


 

typedef struct
{
	int32_t iregisters[REG_COUNT];
	float fregisters[REG_COUNT];

	int pc;
	OpCode* codes;

	StackFrame frame;

	char* filepath;
} CuteEngine;



CuteEngine* CuteEngine_setup(char* filepath);
void CuteEngine_end(CuteEngine* engine);

void CuteEngine_load(CuteEngine* engine);
void CuteEngine_run(CuteEngine* engine);

void CuteEngine_write(CuteEngine* engine, OpCode* code, int count);







