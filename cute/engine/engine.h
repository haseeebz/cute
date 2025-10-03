#include <stdint.h>
#pragma once 

#define OpCode int8_t


typedef struct
{
	int32_t* items;
	int32_t size;
	int32_t capacity;
} Stack;


Stack* Stack_new(int capacity);
void Stack_del(Stack* stack);

void Stack_resize(Stack* stack, int new_cap);
void Stack_push(Stack* stack, int32_t x);
int32_t Stack_pop(Stack* stack);
int32_t Stack_peek(Stack* stack);



typedef struct
{
	Stack* stack;
	int pc;
	char* filepath;
} CuteEngine;

CuteEngine* CuteEngine_setup(char* filepath);
void CuteEngine_end(CuteEngine* engine);

OpCode* CuteEngine_load(CuteEngine* engine);

void CuteEngine_write(CuteEngine* engine, OpCode* code, int count);







