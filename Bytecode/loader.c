#include "include/instr.h"
#include "include/loader.h"
#include <stdint.h>
#include <string.h>


ProgramContext* ProgramContext_new(size_t size)
{
	ProgramContext* context = malloc(sizeof(ProgramContext));

	context->constant_pool = malloc(sizeof(ConstantValue) * size); 
	context->const_count = 0;
	context->_const_cap = size;
	
	context->instrs = malloc(sizeof(Instruction) * size);
	context->instr_count = 0;
	context->_instr_cap = size;

	return context;
};


void ProgramContext_del(ProgramContext* context)
{
	free(context->constant_pool);
	free(context->instrs);
	free(context);
}


void ProgramContext_addInstruction(ProgramContext* context, Instruction instr)
{
	if (context->instr_count >= context->_instr_cap)
	{
		Instruction* instrs = malloc(sizeof(ConstantValue) * context->_instr_cap * 2);
		
		for (int i = 0; i < context->instr_count; i++)
		{
			instrs[i] = context->instrs[i];
		}

		free(context->instrs);
		context->instrs = instrs;
		context->_instr_cap = context->_instr_cap * 2;
	}

	context->instrs[context->instr_count] = instr;
	context->instr_count++;
}
// Appends an instruction to the instructions field

int ProgramContext_addConstInt(ProgramContext* context, int32_t constant)
{
	int8_t bytes[4];
	memcpy(&bytes, &constant, 4);

	if (context->instr_count >= context->_instr_cap)
	{
		Instruction* instrs = malloc(sizeof(ConstantValue) * context->_instr_cap * 2);
		
		for (int i = 0; i < context->instr_count; i++)
		{
			instrs[i] = context->instrs[i];
		}

		free(context->instrs);
		context->instrs = instrs;
		context->_instr_cap = context->_instr_cap * 2;
	}

}
int ProgramContext_addConstFloat(ProgramContext* context, double constant);
// Adds a constant to the pool and returns its index for later referencing.


int ProgramContext_loadFromFile(ProgramContext* context, char* filepath);

int ProgramContext_writeToFile(ProgramContext* context, char* filepath);
