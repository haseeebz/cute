#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"
#include "instr.h"


CuteEngine* CuteEngine_setup(char* filepath)
{
	CuteEngine* engine = malloc(sizeof(CuteEngine));

	int len = strlen(filepath);
	engine->filepath = malloc(sizeof(char)*len);
	strncpy(engine->filepath, filepath, len);

	engine->pc = 0;

	return engine;
}


void CuteEngine_end(CuteEngine* engine)
{
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

	OpCode* codes = malloc(sizeof(OpCode)*100);

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


void CuteEngine_run(CuteEngine* engine)
{
	OpCode code;
	int8_t regr;
	int32_t res;

	while (1)
	{
		code = engine->codes[engine->pc++];

		switch (code) 
		{
		case opLOADi:
			regr = engine->codes[engine->pc++];
			engine->iregisters[regr] = engine->codes[engine->pc++];
			break;
		case opADDi:
			regr = engine->codes[engine->pc++];
			res = engine->iregisters[regr];

			regr = engine->codes[engine->pc++];
			res = res + engine->iregisters[regr];

			regr = engine->codes[engine->pc++];
			engine->iregisters[regr] = res;
			break;

		case opSUBi:
			printf("opSUBi\n"); break;
		case opOUT:
			regr = engine->codes[engine->pc++];
			printf("%d\n", engine->iregisters[regr]);
			break;
		case opHALT: 
			return;
		break;
		}
	}
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