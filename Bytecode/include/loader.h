#pragma once 
#include "instr.h"
#include <cstdint>
#include <stdint.h>
#include <stdlib.h>

#ifdef  __cplusplus 
extern "C" {
#endif

typedef struct
{
	union {int32_t i; double d;} val;
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

	Instruction* instrs;

} ProgramContext;


ProgramContext* ProgramContext_new();
void ProgramContext_del(ProgramContext* context);

void ProgramContext_addInstruction(ProgramContext* context, Instruction instr);
// Appends an instruction to the instructions field

int ProgramContext_addConstInt(ProgramContext* context, int32_t constant);
int ProgramContext_addConstFloat(ProgramContext* context, double constant);
// Adds a constant to the pool and returns its index for later referencing.



#ifdef  __cplusplus 
}
#endif