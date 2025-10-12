#include "include/instr.h"
#include "include/loader.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


ProgramContext* ProgramContext_new()
{
	ProgramContext* context = malloc(sizeof(ProgramContext));
	
	context->instr_count = 0;
	context->_instr_cap = 0;

	return context;
};


void ProgramContext_del(ProgramContext* context)
{
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


int ProgramContext_addInt(ProgramContext* context, int32_t integar)
{
	// Can be optimized.

	InstrByte int_bytes[4];

	memcpy(int_bytes, &integar, sizeof(int_bytes));
	for (int i = 0; i < 4; i++)
	{
		ProgramContext_addInstruction(context, int_bytes[i]);
	}

	return 0;
}


int ProgramContext_writeToFile(ProgramContext* context, char* filepath)
{
	FILE* file = fopen(filepath, "wb");

	if (file == NULL) {return -1;}

	context->header.magic = MAGIC;
	context->header.instr_count = context->instr_count;

	fwrite(&context->header, sizeof(ProgramHeader), 1, file);
	fwrite(&context->instrs, sizeof(InstrByte), context->instr_count, file);
	
	fclose(file);
	return 0;
}



int ProgramContext_loadFromFile(ProgramContext* context, char* filepath) 
{ 
	FILE* file = fopen(filepath, "rb"); 
	
	if (file == NULL) {return -1;} 

	fread(&context->header, sizeof(ProgramHeader), 1, file); 

	context->instr_count = context->header.instr_count; 
	context->instrs = malloc(sizeof(InstrByte) * context->instr_count);
	
	fread(&context->instrs, sizeof(InstrByte), context->instr_count, file); 
	
	fclose(file);
	
	return 0;
}


void ProgramContext_print(ProgramContext* context)
{
	printf("== ProgramContext Dump ==\n");

	printf("Magic: %d\n\n", context->header.magic);

	printf("= Instructions =\n");
	printf("Instr Count: %zu\n", context->instr_count);

	printf("Instruction List:\n");
	
	for (int i = 0; i < context->instr_count; i++)
	{
		printf("%02X ", context->instrs[i]);
	}

	printf("\n");
}
