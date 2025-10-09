#pragma once 
#include "instr.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef  __cplusplus 
extern "C" {
#endif

typedef union
{
	int32_t i; double d;
} ConstantValue;


typedef struct
{
	int32_t magic;
	int32_t constant_pool_index;
	int32_t instructions_index;
} ProgramHeader;


typedef struct 
{
	ProgramHeader header;

	ConstantValue* constant_pool;
	size_t const_count;
	size_t _const_cap;

	Instruction* instrs;
	size_t instr_count;
	size_t _instr_cap;

} ProgramContext;


ProgramContext* ProgramContext_new(size_t size);
void ProgramContext_del(ProgramContext* context);

void ProgramContext_addInstruction(ProgramContext* context, Instruction instr);
// Appends an instruction to the instructions field

int ProgramContext_addConstInt(ProgramContext* context, int32_t constant);
int ProgramContext_addConstFloat(ProgramContext* context, double constant);
// Adds a constant to the pool and returns its index for later referencing.


int ProgramContext_loadFromFile(ProgramContext* context, char* filepath);

int ProgramContext_writeToFile(ProgramContext* context, char* filepath);

#ifdef  __cplusplus 
}
#endif