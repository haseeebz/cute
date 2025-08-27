#include <vector>

#pragma once


enum ContainerType
{
	Int,
	BinaryOp,
	Paran,
	Void
};

enum BinaryOpType {
	Add,
	Sub,
	Div,
	Mul
};

enum ParanType {
	Left,
	Right
};

struct Container
{	

	ContainerType type;
	union {
		int i;
		BinaryOpType op;
		ParanType paran;
	} value;

	Container() {type = ContainerType::Void;}
	Container(int i) {type = ContainerType::Int, value.i = i;}
	Container(BinaryOpType op) {type = ContainerType::BinaryOp, value.op = op;}
	Container(ParanType paran) {type = ContainerType::Paran, value.paran = paran;}
};

using ContainerVec = std::vector<Container>;