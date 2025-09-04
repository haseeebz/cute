#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/containers.h"


void printContainer(Container* con, bool endline)
{

	if (con->type == Int)
	{
		printf("[Int %d]", con->value.i);
	}
	else if (con->type == BinaryOp)
	{
		printf("[BinaryOp %d]", con->value.bop);
		
	}

	if (endline) {printf("\n");}
}


Container newIntContainer(int i)
{
	Container con;
	con.type = Int;
	con.value.i = i;
	return con;
}


Container newBinaryOpContainer(BinaryOpType op)
{
	Container con;
	con.type = BinaryOp;
	con.value.bop = op;
	return con;
}


ContainerStack* newContainerStack(int capacity)
{
	ContainerStack* stack = malloc(sizeof(ContainerStack));
	stack->capacity = capacity;
	stack->size = 0;

	stack->cons = malloc(sizeof(Container)*capacity);

	return stack;
}


Container ContainerStack_resize(ContainerStack* stack);




void ContainerStack_push(ContainerStack* stack, Container con)
{
	stack->cons[stack->size] = con;
	stack->size++;
}




Container ContainerStack_pop(ContainerStack* stack);
Container ContainerStack_peek(ContainerStack* stack);
void delContainerStack(ContainerStack* stack);
void printContainerStack(ContainerStack* stack);
