#include <stdio.h>
#include <stdbool.h>
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
