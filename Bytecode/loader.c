#include "include/instr.h"
#include "include/loader.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


ProgramContext* ProgramContext_new()
{
	ProgramContext* context = malloc(sizeof(ProgramContext));

	context->const_count = 0;
	context->_const_cap = 0;
	
	context->instr_count = 0;
	context->_instr_cap = 0;

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
		Instruction* instrs = malloc(sizeof(ConstantValue) * (context->_instr_cap + 1) * 2);
		
		for (int i = 0; i < context->instr_count; i++)
		{
			instrs[i] = context->instrs[i];
		}

		free(context->instrs);
		context->instrs = instrs;
		context->_instr_cap = context->_instr_cap+1 * 2;
	}

	context->instrs[context->instr_count] = instr;
	context->instr_count++;
}


int ProgramContext_addConstant(ProgramContext* context, ConstantValue constant)
{

	if (context->const_count >= context->_const_cap)
	{
		ConstantValue* constants = malloc(sizeof(ConstantValue) * (context->_const_cap+1) * 2);
		
		for (int i = 0; i < context->instr_count; i++)
		{
			constants[i] = context->constant_pool[i];
		}

		free(context->constant_pool);
		context->constant_pool = constants;
		context->_const_cap = context->_const_cap+1 * 2;
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

	context->header.magic = MAGIC;
	context->header.constant_pool_index = sizeof(ProgramHeader);
	context->header.constant_count = context->const_count;
	context->header.instr_count = context->instr_count;


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
	fwrite(context->instrs, sizeof(InstrByte), context->instr_count, file);

	fp_index = ftell(file);

	fseek(file, 0, SEEK_SET);
	fwrite(&context->header, sizeof(ProgramHeader), 1, file);

	return 0;
}

int ProgramContext_loadFromFile(ProgramContext* context, char* filepath)
{
	FILE* file = fopen(filepath, "rb");

	if (file == NULL) {return -1;}
	
	fread(&context->header, sizeof(ProgramHeader), 1, file);
	
	context->const_count = context->header.constant_count;
	context->constant_pool = malloc(sizeof(ConstantValue) * context->const_count);

	for (int i = 0; i < context->header.constant_count; i++)
	{
		fread(&context->constant_pool[i].type, sizeof(int8_t), 1, file);

		switch (context->constant_pool[i].type) 
		{
			case constInt:
			fread(&context->constant_pool[i].val.i, sizeof(int32_t), 1, file);
			break;
			case constDouble:
			fread(&context->constant_pool[i].val.d, sizeof(int32_t), 1, file);
			break;
		}

	}

	context->instr_count = context->header.instr_count;
	context->instrs = malloc(sizeof(InstrByte)* context->instr_count);
	fread(context->instrs, sizeof(InstrByte), context->instr_count, file);

	return 0;
}

