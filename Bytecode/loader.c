#include "include/instr.h"
#include "include/loader.h"
#include <stdint.h>
#include <stdio.h>
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


int ProgramContext_addConstant(ProgramContext* context, ConstantValue constant)
{

	if (context->const_count >= context->_const_cap)
	{
		ConstantValue* constants = malloc(sizeof(ConstantValue) * context->_const_cap * 2);
		
		for (int i = 0; i < context->instr_count; i++)
		{
			constants[i] = context->constant_pool[i];
		}

		free(context->constant_pool);
		context->constant_pool = constants;
		context->_const_cap = context->_const_cap * 2;
	}

	context->constant_pool[context->const_count] = constant;
	context->const_count++;
	return context->const_count-1;
}


int ProgramContext_writeToFile(ProgramContext* context, char* filepath)
{
	FILE* file = fopen(filepath, "wb");

	if (file == NULL) {return -1;}
	long fp_index;


	fwrite(&context->header, sizeof(ProgramHeader), 1, file);

	context->header.constant_pool_index = sizeof(ProgramHeader);


	for (int i = 0; i < context->const_count; i++)
	{
		fwrite(&context->constant_pool[i].type, sizeof(int8_t), 1, file);

		switch (context->constant_pool[i].type) 
		{
			case constInt:
			fwrite(&context->constant_pool[i].val.i, sizeof(int32_t), 1, file);
			break;
			case constDouble:
			fwrite(&context->constant_pool[i].val.d, sizeof(int32_t), 1, file);
			break;
		}
	}

	fp_index = ftell(file);
	
	context->header.instructions_index = fp_index;

	fwrite(context->instrs, sizeof(Instruction), context->instr_count, file);
	
	return 0;
}

int ProgramContext_loadFromFile(ProgramContext* context, char* filepath);

