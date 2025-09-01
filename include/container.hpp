#include <vector>

#pragma once


enum ContainerType
{
	Int,
	Double,
	BinaryOp,
	Paran,
	Void
};

enum BinaryOpType {
	Add,
	Sub,
	Mul,
	Div,
	Pow
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
		double d;
		BinaryOpType op;
		ParanType paran;
	} value;

	Container() {type = ContainerType::Void;}
	Container(int i) {type = ContainerType::Int, value.i = i;}
	Container(double d) {type = ContainerType::Double, value.d = d;}
	Container(BinaryOpType op) {type = ContainerType::BinaryOp, value.op = op;}
	Container(ParanType paran) {type = ContainerType::Paran, value.paran = paran;}
};

using ContainerVec = std::vector<Container>;