#include <stdbool.h>

#pragma once

typedef enum 
{
	atomVoid,
	atomInt,
	atomFloat,
	atomOp,
} CuteAtomType;


typedef int CuteInt;
typedef double CuteFloat;

// Arranged according to default precedence.
typedef enum 
{
	opAdd, opSub, opMul, opDiv
} CuteOperator;



typedef struct 
{
	CuteAtomType type;
	union {
		CuteInt i;
		CuteFloat f;
		CuteOperator op;
	} val;
} CuteAtom;



void CuteAtom_print(CuteAtom* atom, bool endline);

CuteAtom CuteAtom_makeVoid();
CuteAtom CuteAtom_makeInt(CuteInt i);
CuteAtom CuteAtom_makeFloat(CuteFloat f);
CuteAtom CuteAtom_makeOperator(CuteOperator op);

void CuteAtom_del(CuteAtom* atom);


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