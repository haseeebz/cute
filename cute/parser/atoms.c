#include "atoms.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


void CuteAtom_print(CuteAtom* atom, bool endline)
{
	if (atom->type == Int)
	{
		printf("[ Int %d ] ", atom->val.i);
	}
	else if (atom->type == BinaryOp)
	{
		printf("[ BinaryOp %c ] ", atom->val.c);
	}
	else 
	{
		printf("[ Undef ] ");
	}

	if (endline) { printf("\n"); }
}


void CuteAtomStack_print(CuteAtomStack* stack)
{
	for (int i = 0; i < stack->size; i++)
	{
		CuteAtom atom = stack->atoms[i];
		CuteAtom_print(&atom, false);
	}
	printf("\n");
}


CuteAtomStack* CuteAtomStack_new(int capacity)
{
	CuteAtomStack* stack = malloc(sizeof(CuteAtomStack));
	stack->atoms = malloc(sizeof(CuteAtom)*capacity);
	stack->capacity = capacity;
	stack->size = 0;
	return stack;
}


void CuteAtomStack_del(CuteAtomStack* stack)
{
	free(stack->atoms);
	free(stack);
}


void CuteAtomStack_resize(CuteAtomStack* stack, int capacity)
{
	if (capacity <= stack->capacity)
	{
		return;
	}

	CuteAtom* atoms = malloc(sizeof(CuteAtom)*capacity);
	
	for (int i = 0; i <= stack->size; i++)
	{
		atoms[i] = stack->atoms[i];
	}
	free(stack->atoms);
	stack->atoms = atoms;
	stack->capacity = capacity;
}


bool CuteAtomStack_isEmpty(CuteAtomStack* stack)
{
	if (stack->size > 0) { return false; }
	return true;
}


void CuteAtomStack_push(CuteAtomStack* stack, CuteAtom atom)
{
	if (stack->size >= stack->capacity)
	{
		CuteAtomStack_resize(stack, stack->capacity * 2);	
	}

	stack->atoms[stack->size] = atom;
	stack->size++;
}


CuteAtom CuteAtomStack_pop(CuteAtomStack* stack)
{
	stack->size--;
	return stack->atoms[stack->size];
}

CuteAtom CuteAtomStack_peek(CuteAtomStack* stack)
{
	return stack->atoms[stack->size-1];
}