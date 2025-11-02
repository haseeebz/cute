#include <stdint.h>

#pragma once 


enum BinaryOpType
{
	binaryADD,
	binarySUB,
	binaryMUL,
	binaryDIV,
};

// Node definition

enum NodeType
{
	nodeInt,
	nodeFloat,
	nodeBinaryOp
};


struct Node
{
	
	struct BinaryOp
	{
		BinaryOpType op;
		Node* lhs;
		Node* rhs;
	};

	NodeType type;

	union
	{
		int i;
		float f;
		BinaryOp bop;
	};

	Node(int i): i(i) {};
	Node(float f): f(f) {};

	Node(BinaryOpType op, Node* lhs, Node* rhs): bop{.op = op, .lhs = lhs, .rhs = rhs} {};

	~Node();
};


