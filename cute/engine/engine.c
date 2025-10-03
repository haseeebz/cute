#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"


Stack* Stack_new(int capacity)
{
	Stack* stack = malloc(sizeof(Stack));
	stack->capacity = capacity;
	stack->size = 0;
	stack->items = malloc(sizeof(int32_t)*capacity);
	return stack;
}


void Stack_del(Stack* stack)
{
	free(stack->items);
	free(stack);
}


void Stack_resize(Stack* stack, int new_cap)
{
	if (new_cap <= stack->capacity) {return;}

	int32_t* items = malloc(sizeof(int32_t)*new_cap);

	for (int i = 0; i < stack->size; i++)
	{
		items[i] = stack->items[i];
	}

	free(stack->items);
	stack->items = items;
}	


void Stack_push(Stack* stack, int32_t x)
{
	if (stack->size >= stack->capacity)
	{
		Stack_resize(stack, stack->capacity * 2);
	}

	stack->items[stack->size] = x;
	stack->size++;
}


int32_t Stack_pop(Stack* stack)
{
	return stack->items[stack->size--];
}


int32_t Stack_peek(Stack* stack)
{
	return stack->items[stack->size-1];
}


CuteEngine* CuteEngine_setup(char* filepath)
{
	CuteEngine* engine = malloc(sizeof(CuteEngine));

	int len = strlen(filepath);
	engine->filepath = malloc(sizeof(char)*len);
	strncpy(engine->filepath, filepath, len);

	engine->stack = Stack_new(len);

	engine->pc = 0;

	return engine;
}


void CuteEngine_end(CuteEngine* engine)
{
	free(engine->filepath);
	free(engine->stack);
	free(engine);
}

OpCode* CuteEngine_load(CuteEngine* engine)
{
	FILE* file = fopen(engine->filepath, "rb");

	if (file == NULL) 
	{
		printf("Could not load file: '%s'\n", engine->filepath);
		fclose(file);
		exit(EXIT_FAILURE);
	}

	OpCode* codes = malloc(sizeof(OpCode)*100);

	OpCode code;
	int index = 0;

	while (fread(&code, sizeof(OpCode), 1, file) == 1)
	{
		codes[index] = code;
		index++;
	}

	fclose(file);

	return codes;
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

	fwrite(code, sizeof(OpCode), count, file);

	fclose(file);
}