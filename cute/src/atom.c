#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/atom.h"


void CuteAtom_print(CuteAtom* atom, bool endline)
{

	if (atom->type == atomInt)
	{
		printf("[ Int %d ]", atom->value.i);
	}
	else if (atom->type == atomDouble)
	{
		printf("[ Double %lf ]", atom->value.d);
	}
	else if (atom->type == atomBinaryOp)
	{
		printf("[ BinaryOp %d ]", atom->value.bop);
	}
	else if (atom->type == atomVoid)
	{
		printf("[ Void ]");
	}

	if (endline) {printf("\n");}
}


CuteAtom CuteAtom_makeVoid()
{
	CuteAtom atom;
	atom.type = atomVoid;
	return atom;
}


CuteAtom CuteAtom_makeInt(int i)
{
	CuteAtom atom;
	atom.type = atomInt;
	atom.value.i = i;
	return atom;
}


CuteAtom CuteAtom_makeDouble(double d)
{
	CuteAtom atom;
	atom.type = atomDouble;
	atom.value.d = d;
	return atom;
}


CuteAtom CuteAtom_makeBinaryOp(BinaryOpType op)
{
	CuteAtom atom;
	atom.type = atomBinaryOp;
	atom.value.bop = op;
	return atom;
}


CuteAtomStack* CuteAtomStack_new(int capacity)
{
	CuteAtomStack* stack = malloc(sizeof(CuteAtomStack));
	stack->capacity = capacity;
	stack->size = 0;

	stack->atoms = malloc(sizeof(CuteAtom)*capacity);

	return stack;
}


void CuteAtomStack_resize(CuteAtomStack* stack, int capacity)
{
	if (stack->capacity >= capacity) {return;}

	CuteAtom* copied_atoms = malloc(sizeof(CuteAtom) * capacity);

	for (int i = 0; i < stack->size; i++)
	{
		copied_atoms[i] = stack->atoms[i];
	}

	free(stack->atoms);
	stack->atoms = copied_atoms;
	stack->capacity = capacity;
}


void CuteAtomStack_push(CuteAtomStack* stack, CuteAtom atom)
{
	if (stack->size >= stack->capacity)
	{
		CuteAtomStack_resize(stack, stack->capacity*2);
	}
	stack->atoms[stack->size++] = atom;
}


CuteAtom CuteAtomStack_pop(CuteAtomStack* stack)
{
	if (stack->size <= 0) 
	{
		CuteAtom atom = {.type = atomVoid};
		return atom;
	}
	stack->size--;
	CuteAtom atom = stack->atoms[stack->size];
	return atom;
}


CuteAtom CuteAtomStack_peek(CuteAtomStack* stack)
{
	if (stack->size < 1) 
	{
		CuteAtom atom = {.type = atomVoid};
		return atom;
	}

	CuteAtom atom = stack->atoms[stack->size-1];
	return atom;	
}


void CuteAtomStack_del(CuteAtomStack* stack)
{
	free(stack->atoms);
	free(stack);
}


void CuteAtomStack_print(CuteAtomStack* stack)
{
	CuteAtom current;
	for (int i = 0; i < stack->size; i++)
	{
		current = stack->atoms[i];
		CuteAtom_print(&current, false);
	}
	printf("\n");
}
