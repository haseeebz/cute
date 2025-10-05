#include <stdint.h>
#pragma once 


typedef union
{
	int32_t i;
	float f;
} GenericMemory;

typedef struct
{
	GenericMemory memory[100];
	int size;
} StackFrame;

