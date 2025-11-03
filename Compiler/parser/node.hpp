#include <stdint.h>
#include <string>

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
	nodeBinaryOp,
	nodeEmpty
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

	Node() : type(NodeType::nodeEmpty) {};
	Node(int i): type(NodeType::nodeInt), i(i) {};
	Node(float f): type(NodeType::nodeFloat), f(f) {};

	Node(BinaryOpType op, Node* lhs, Node* rhs): type(NodeType::nodeBinaryOp), bop{.op = op, .lhs = lhs, .rhs = rhs} {};

	~Node();

	std::string str(bool endline = true);
};


