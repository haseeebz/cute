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


typedef struct {
	Container* cons;
	int size;
	int capacity;
} ContainerStack;

ContainerStack* newContainerStack(int capacity);
Container ContainerStack_resize(ContainerStack* stack);
void ContainerStack_push(ContainerStack* stack, Container con);
Container ContainerStack_pop(ContainerStack* stack);
Container ContainerStack_peek(ContainerStack* stack);
void delContainerStack(ContainerStack* stack);
void printContainerStack(ContainerStack* stack);
