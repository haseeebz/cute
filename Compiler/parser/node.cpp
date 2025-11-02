#include <iostream>
#include "node.hpp"


Node::~Node()
{
	if (type == NodeType::nodeBinaryOp)
	{
		delete bop.lhs;
		delete bop.rhs;
	}
}


void Node::print(int depth = 0)
{
	char BinaryMap[] = {'+', '-', '*', '/'};

	for (int i = 0; i < depth; i++)
	{
		std::cout << "  ";
	}

	if (type == NodeType::nodeInt)
	{
		std::cout << i << std::endl;
	}

	if (type == NodeType::nodeBinaryOp)
	{
		std::cout << BinaryMap[bop.op] << std::endl;
		bop.lhs->print(depth + 1);
		bop.rhs->print(depth + 1);
	}

	if (type == NodeType::nodeEmpty)
	{
		std::cout << "#empty" << std::endl;
	}
}