#include <stdbool.h>
#pragma once

typedef enum 
{
	Int,
	BinaryOp,

} CuteAtomType;


typedef struct 
{
	CuteAtomType type;
	union {
		int i;
		char c;
	} val;
} CuteAtom;


void CuteAtom_print(CuteAtom* atom, bool endline);


typedef struct
{
	CuteAtom* atoms;
	int size;
	int capacity; 
} CuteAtomStack;


void CuteAtomStack_print(CuteAtomStack* stack);
CuteAtomStack* CuteAtomStack_new(int capacity);
void CuteAtomStack_del(CuteAtomStack* stack);
void CuteAtomStack_resize(CuteAtomStack* stack, int capacity);
bool CuteAtomStack_isEmpty(CuteAtomStack* stack);
void CuteAtomStack_push(CuteAtomStack* stack, CuteAtom atom);
CuteAtom CuteAtomStack_pop(CuteAtomStack* stack);
CuteAtom CuteAtomStack_peek(CuteAtomStack* stack);