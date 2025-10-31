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
	NodeType type;
	union val
	{
		int i;
		float f;

		struct bop
		{
			BinaryOpType bop;
			Node* rhs;
			Node* lhs;
		};

	};
};


