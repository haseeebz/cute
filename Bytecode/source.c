#include "include/cuteByte.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


ProgramSource* ProgramSource_new()
{
	ProgramSource* program = malloc(sizeof(ProgramSource));
	
	program->instr_count = 0;
	program->_instr_cap = 0;

	return program;
};


void ProgramSource_del(ProgramSource* program)
{
	free(program->instrs);
	free(program);
}


void ProgramSource_addInstruction(ProgramSource* program, Instruction instr)
{
	if (program->instr_count >= program->_instr_cap)
	{
		Instruction* instrs = malloc(sizeof(InstrByte) * (program->_instr_cap + 1) * 2);
		
		for (int i = 0; i < program->instr_count; i++)
		{
			instrs[i] = program->instrs[i];
		}

		free(program->instrs);
		program->instrs = instrs;
		program->_instr_cap = program->_instr_cap+1 * 2;
	}

	program->instrs[program->instr_count] = instr;
	program->instr_count++;
}


int ProgramSource_addInt(ProgramSource* program, int32_t integar)
{
	// Can be optimized.

	InstrByte int_bytes[4];

	memcpy(int_bytes, &integar, sizeof(int_bytes));
	for (int i = 0; i < 4; i++)
	{
		ProgramSource_addInstruction(program, int_bytes[i]);
	}

	return 0;
}


int ProgramSource_writeToFile(ProgramSource* program, char* filepath)
{
	FILE* file = fopen(filepath, "wb");

	if (file == NULL) {return -1;}

	program->header.magic = MAGIC;
	program->header.instr_count = program->instr_count;

	fwrite(&program->header, sizeof(ProgramHeader), 1, file);
	fwrite(&program->instrs, sizeof(InstrByte), program->instr_count, file);
	
	fclose(file);
	return 0;
}



int ProgramSource_loadFromFile(ProgramSource* program, char* filepath) 
{ 
	FILE* file = fopen(filepath, "rb"); 
	
	if (file == NULL) {return -1;} 

	fread(&program->header, sizeof(ProgramHeader), 1, file); 

	program->instr_count = program->header.instr_count; 
	program->instrs = malloc(sizeof(InstrByte) * program->instr_count);

	
	int read = fread(&program->instrs, sizeof(InstrByte), program->instr_count, file); 
	fclose(file);

	printf("Read Instructions: %d, Total Count: %d", read, program->instr_count);
	
	return 0;
}


void ProgramSource_print(ProgramSource* program)
{
	printf("== ProgramSource Dump ==\n");

	printf("Magic: %d\n\n", program->header.magic);

	printf("= Instructions =\n");
	printf("Instr Count: %zu\n", program->instr_count);

	printf("Instruction List:\n");
	
	for (size_t i = 0; i < program->instr_count; i++)
	{
		printf("%d ", program->instrs[i]);
	}

	printf("\n");
}
