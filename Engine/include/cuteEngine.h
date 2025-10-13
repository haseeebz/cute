#include "cuteInstr.h"
#include "cuteProgImg.h"

#include "../atom.h"
#include "../context.h"

#pragma once

typedef struct
{
	ExecutionContext* ctx;
	ProgramImage* program;
} CuteEngine;


void CuteEngine_init(CuteEngine* engine);
void CuteEngine_end(CuteEngine* engine);

void CuteEngine_exec(CuteEngine* engine, ProgramImage* program);
