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
	Float,
	BinaryOp
} ContainerType;


typedef union {
	int i;
	float f;
	BinaryOpType bop;
} ContainerValue;


typedef struct {
	ContainerType type;
	ContainerValue value;
} Container;


void Container_print(Container* con, bool endline);

Container Container_makeVoid();
Container Container_makeInt(int i);
Container Container_makeFloat(float f);
Container Container_makeBinaryOp(BinaryOpType op);


typedef struct {
	Container* cons;
	int size;
	int capacity;
} ContainerStack;

ContainerStack* ContainerStack_new(int capacity);
void ContainerStack_resize(ContainerStack* stack, int capacity);
void ContainerStack_push(ContainerStack* stack, Container con);
Container ContainerStack_pop(ContainerStack* stack);
Container ContainerStack_peek(ContainerStack* stack);
void ContainerStack_del(ContainerStack* stack);
void ContainerStack_print(ContainerStack* stack);
