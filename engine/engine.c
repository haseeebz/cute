#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frame.h"
#include "include/engine.h"
#include "instr.h"
#include "memory.h"



CuteEngine* CuteEngine_setup(char* filepath)
{
	CuteEngine* engine = malloc(sizeof(CuteEngine));

	int len = strlen(filepath);
	engine->filepath = malloc(sizeof(char)*len);
	strncpy(engine->filepath, filepath, len);

	engine->pc = 0;

	engine->exestack = ExecutionStack_new(10);
	return engine;
}


void CuteEngine_end(CuteEngine* engine)
{
	ExecutionStack_del(engine->exestack);
	free(engine->filepath);
	free(engine);
}


void CuteEngine_load(CuteEngine* engine)
{
	FILE* file = fopen(engine->filepath, "rb");

	if (file == NULL) 
	{
		printf("Could not load file: '%s'\n", engine->filepath);
		fclose(file);
		exit(EXIT_FAILURE);
	}

	OpCode* codes = malloc(sizeof(OpCode) * 200);

	OpCodeByte raw;
	int index = 0;
	
	while (fread(&raw, sizeof(OpCodeByte), 1, file) == 1)
	{
		codes[index] = (OpCode) raw;
		index++;
	}

	if (file != NULL) { fclose(file); }

	engine->codes = codes;
}


void CuteEngine_write(CuteEngine* engine, OpCode* code, int count)
{
	
	FILE* file = fopen(engine->filepath, "wb");

	if (file == NULL) 
	{
		printf("Could not load file: '%s'\n", engine->filepath);
		fclose(file);
		exit(EXIT_FAILURE);
	}

	OpCodeByte raw;
	for (int i = 0; i < count; i++)
	{
		raw = (OpCodeByte) code[i];
		fwrite(&raw, sizeof(OpCodeByte), 1, file);
	}
	
	fclose(file);
}




void CuteEngine_run(CuteEngine* engine)
{
	OpCode code;


	while (1)
	{
		code = engine->codes[engine->pc++];
		
		switch (code)
		{
			

		
		}
	}
}


