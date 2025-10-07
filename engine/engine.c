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

	engine->exestack = ExecutionStack_new(5);
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
		printf("%X ", raw);
		codes[index] = (OpCode) raw;
		index++;
	}
	printf("\n");

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
	StackItem res;
	StackItem item1;
	StackItem item2;

	while (1)
	{
		code = engine->codes[engine->pc++];

		#ifdef DEBUG 
		printf("Executing instruction(%X)\n", code); 
		#endif
		
		switch (code)
		{

		case opEXIT:
			return;

		case opLCONi:
			res.i = engine->codes[engine->pc++];
			ExecutionStack_push(engine->exestack, res);

			#ifdef DEBUG 
			printf("	Loaded Constant[%d]\n", res.i); 
			#endif

			break;

		case opLOADi:
			item1.i = engine->codes[engine->pc++];
			res = engine->exestack->memory[item1.i];
			ExecutionStack_push(engine->exestack, res);

			#ifdef DEBUG 
			printf("	Loaded Integar[%d] from address[%d]\n", res.i, item1.i); 
			#endif

			break;

		case opSTORi:
			item1 = ExecutionStack_peek(engine->exestack);
			item2.i = engine->codes[engine->pc++];
			engine->exestack->memory[item2.i] = item1;

			#ifdef DEBUG 
			printf("	Stored Integar[%d] to address[%d]\n", item1.i, item2.i); 
			#endif

			break;
		
		case opADDi:
			item2= ExecutionStack_pop(engine->exestack);
			item1 = ExecutionStack_pop(engine->exestack);
			res.i = item1.i + item2.i;
			ExecutionStack_push(engine->exestack, res);

			#ifdef DEBUG 
			printf("	Added Integar [%d] and [%d]\n", item1.i, item2.i); 
			#endif

			break;

		case opSUBi:
			item2 = ExecutionStack_pop(engine->exestack);
			item1 = ExecutionStack_pop(engine->exestack);
			res.i = item1.i - item2.i;
			ExecutionStack_push(engine->exestack, res);

			#ifdef DEBUG 
			printf("	Subtracted Integar [%d] and [%d]\n", item1.i, item2.i); 
			#endif

			break;

		case opMULi:
			item2 = ExecutionStack_pop(engine->exestack);
			item1 = ExecutionStack_pop(engine->exestack);
			res.i = item1.i * item2.i;
			ExecutionStack_push(engine->exestack, res);

			#ifdef DEBUG 
			printf("	Multiplied Integar [%d] and [%d]\n", item1.i, item2.i); 
			#endif


			break;

		case opDIVi:
			item2 = ExecutionStack_pop(engine->exestack);
			item1 = ExecutionStack_pop(engine->exestack);
			res.i = item1.i / item2.i;
			ExecutionStack_push(engine->exestack, res);

			#ifdef DEBUG 
			printf("	Divided Integar [%d] and [%d]\n", item1.i, item2.i); 
			#endif

			break;

		case opJMPx:
			engine->pc = engine->pc + engine->codes[engine->pc++]; 

			#ifdef DEBUG 
			printf("	Jumped to [%d] Offset = [%d]\n", engine->pc, engine->pc-1); 
			#endif

			break;

		case opJMPe:
			item1 = ExecutionStack_pop(engine->exestack);
			if (item1.i != 0)
			{
				engine->pc = engine->codes[engine->pc];
				#ifdef DEBUG 
				printf("	Jumped to [%d]\n", engine->pc); 
				#endif
				continue;
			}
			engine->pc++;

			#ifdef DEBUG 
			printf("	Did not Jump. Offset = [%d]\n",  engine->pc-1); 
			#endif

			break;

		case opEQi:
			item2 = ExecutionStack_pop(engine->exestack);
			item1 = ExecutionStack_pop(engine->exestack);
			res.i = (item1.i != item2.i);
			ExecutionStack_push(engine->exestack, res);

			#ifdef DEBUG 
			printf("	Statement equal = %d\n", res.i); 
			#endif

			break;

		case opOUT:
			res = ExecutionStack_peek(engine->exestack);

			#ifdef DEBUG 
			printf("	Output = "); 
			#endif

			printf("%d\n", res.i);
			break;

		default:
			return;
		}
	}
}


