#include <stdbool.h>

#pragma once

typedef enum {
	Add,
	Sub,
	Mul,
	Div
} BinaryOpType;


typedef enum {
	Void,
	Int,
	BinaryOp
} ContainerType;


typedef union {
	int i;
	BinaryOpType bop;
} ContainerValue;


typedef struct {
	ContainerType type;
	ContainerValue value;
} Container;


void printContainer(Container* con, bool endline);

Container newIntContainer(int i);
Container newBinaryOpContainer(BinaryOpType op);

