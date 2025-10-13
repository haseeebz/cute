#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "cuteInstr.h"

#pragma once 

#define MAGIC 0x10211225


#ifdef  __cplusplus 
extern "C" {
#endif


typedef struct 
{
	enum {constInt, constFloat} type;
	union {int32_t i; float f;} val;
} ProgramConst;


typedef struct
{
	int32_t magic;
} ProgramHeader;


typedef struct
{
	ProgramHeader header;

	Instruction* instrs;
	int32_t instr_count;
	int32_t _instr_cap;

	ProgramConst* constants;
	int32_t const_count;
	int32_t _const_cap;

} ProgramImage;

ProgramImage* ProgramImage_new();
void ProgramImage_del(ProgramImage* program);

void ProgramImage_appendInstruction(ProgramImage* program, Instruction instr);

int ProgramImage_addConstant(ProgramImage* program, ProgramConst constant);

int ProgramImage_addConstInt(ProgramImage* program, int32_t i);
int ProgramImage_addConstFloat(ProgramImage* program, float f);


#ifdef  __cplusplus 
}
#endif