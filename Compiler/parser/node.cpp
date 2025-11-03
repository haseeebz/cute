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


void Node::print(bool endline)
{
	char BinaryMap[] = {'+', '-', '*', '/'};


	if (type == NodeType::nodeInt)
	{
		std::cout << i;
	}

	if (type == NodeType::nodeBinaryOp)
	{
		std::cout << "(" << BinaryMap[bop.op];
		std::cout << " ";
		bop.lhs->print(false);
		std::cout << " ";
		bop.rhs->print(false);
		std::cout << ")";
	}

	if (type == NodeType::nodeEmpty)
	{
		std::cout << "null";
	}



	if (endline) {std::cout << std::endl;}
}