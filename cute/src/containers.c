#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/containers.h"


void Container_print(Container* con, bool endline)
{

	if (con->type == Int)
	{
		printf("[ Int %d ]", con->value.i);
	}
	else if (con->type == BinaryOp)
	{
		printf("[ BinaryOp %d ]", con->value.bop);
	}
	else if (con->type == Void)
	{
		printf("[ Void ]");
	}

	if (endline) {printf("\n");}
}


Container Container_makeVoid()
{
	Container con;
	con.type = Void;
	return con;
}


Container Container_makeInt(int i)
{
	Container con;
	con.type = Int;
	con.value.i = i;
	return con;
}


Container Container_makeFloat(float f)
{
	Container con;
	con.type = Float;
	con.value.f = f;
	return con;
}


Container Container_makeBinaryOp(BinaryOpType op)
{
	Container con;
	con.type = BinaryOp;
	con.value.bop = op;
	return con;
}


ContainerStack* ContainerStack_new(int capacity)
{
	ContainerStack* stack = malloc(sizeof(ContainerStack));
	stack->capacity = capacity;
	stack->size = 0;

	stack->cons = malloc(sizeof(Container)*capacity);

	return stack;
}


void ContainerStack_resize(ContainerStack* stack, int capacity)
{
	if (stack->capacity >= capacity) {return;}

	Container* copied_cons = malloc(sizeof(Container) * capacity);

	for (int i = 0; i < stack->size; i++)
	{
		copied_cons[i] = stack->cons[i];
	}

	free(stack->cons);
	stack->cons = copied_cons;
	stack->capacity = capacity;
}


void ContainerStack_push(ContainerStack* stack, Container con)
{
	if (stack->size >= stack->capacity)
	{
		ContainerStack_resize(stack, stack->capacity*2);
	}
	stack->cons[stack->size++] = con;
}


Container ContainerStack_pop(ContainerStack* stack)
{
	if (stack->size <= 0) 
	{
		Container con = {.type = Void};
		return con;
	}
	stack->size--;
	Container con = stack->cons[stack->size];
	return con;
}


Container ContainerStack_peek(ContainerStack* stack)
{
	if (stack->size < 1) 
	{
		Container con = {.type = Void};
		return con;
	}

	Container con = stack->cons[stack->size-1];
	return con;	
}


void ContainerStack_del(ContainerStack* stack)
{
	free(stack->cons);
	free(stack);
}


void ContainerStack_print(ContainerStack* stack)
{
	Container current;
	for (int i = 0; i < stack->size; i++)
	{
		current = stack->cons[i];
		Container_print(&current, false);
	}
	printf("\n");
}
