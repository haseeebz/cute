#include <stdint.h>
#include "instr.h"

#pragma once 

#define iREGR 8
#define fREGR 8

typedef struct
{
	int32_t iregisters[iREGR];
	float fregisters[fREGR];

	int pc;
	OpCode* codes;
	char* filepath;
} CuteEngine;


CuteEngine* CuteEngine_setup(char* filepath);
void CuteEngine_end(CuteEngine* engine);

void CuteEngine_load(CuteEngine* engine);
void CuteEngine_run(CuteEngine* engine);

void CuteEngine_write(CuteEngine* engine, OpCode* code, int count);







