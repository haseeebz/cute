#include "instr.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#pragma once 

#define MAGIC 0x10211225


#ifdef  __cplusplus 
extern "C" {
#endif

typedef struct
{
	enum { constInt = 0x01, constDouble = 0x02} type;
	union { int32_t i; double d; } val;
} ConstantValue;


typedef struct
{
	int32_t magic;
	int32_t instr_count;
} ProgramHeader;

typedef struct 
{
	ProgramHeader header;

	//ConstantValue* constant_pool;
	//size_t const_count;
	//size_t _const_cap;

	Instruction* instrs;
	size_t instr_count;
	size_t _instr_cap;

} ProgramContext;


ProgramContext* ProgramContext_new();
void ProgramContext_del(ProgramContext* context);

void ProgramContext_addInstruction(ProgramContext* context, Instruction instr);

int ProgramContext_addInt(ProgramContext* context, int32_t integar);


int ProgramContext_loadFromFile(ProgramContext* context, char* filepath);
int ProgramContext_writeToFile(ProgramContext* context, char* filepath);

void ProgramContext_print(ProgramContext* context);

#ifdef  __cplusplus 
}
#endif