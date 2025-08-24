#include <vector>

#pragma once


enum ContainerType
{
	Int,
	BinaryOp,
	Void
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

	Container() {type = ContainerType::Void;}
	Container(int i) {type = ContainerType::Int, value.i = i;}
	Container(BinaryOpType op) {type = ContainerType::BinaryOp, value.op = op;}
};

using ContainerVec = std::vector<Container>;