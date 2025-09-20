#include <stdbool.h>

#pragma once

typedef enum 
{
	atomVoid,
	atomInt,
	atomFloat,
	atomBinaryOp,
} CuteAtomType;


typedef struct 
{
	CuteAtomType type;
	void* val;
} CuteAtom;


typedef int CuteInt;
typedef double CuteFloat;
typedef enum {ADD, SUB, DIV, MUL} CuteBinaryOp;



void CuteAtom_print(CuteAtom* atom, bool endline);

CuteAtom CuteAtom_makeInt(CuteInt i);
CuteAtom CuteAtom_makeFloat(CuteFloat f);
CuteAtom CuteAtom_makeBinaryOp(CuteBinaryOp op);

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