#include <vector>

#pragma once


enum ContainerType
{
	Int,
	BinaryOp
};

enum BinaryOpType {
	Add,
	Sub,
	Div,
	Mul
};

struct Container
{	

	ContainerType type;
	union {
		int i;
		BinaryOpType op;
	} value;

	Container(int i) {type = ContainerType::Int, value.i = i;}
	Container(BinaryOpType op) {type = ContainerType::BinaryOp, value.op = op;}
};

using ContainerVec = std::vector<Container>;