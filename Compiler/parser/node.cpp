#include <iostream>
#include <string>
#include "node.hpp"


Node::~Node()
{
	if (type == NodeType::nodeBinaryOp)
	{
		delete bop.lhs;
		delete bop.rhs;
	}
}


std::string Node::str(bool endline)
{
	std::string str;

	char BinaryMap[] = {'+', '-', '*', '/'};


	if (type == NodeType::nodeInt)
	{
		str.append(std::to_string(i));
	}

	if (type == NodeType::nodeBinaryOp)
	{
		str.append("(");
		str.push_back(BinaryMap[bop.op]);
		str.append(" ");
		str.append(bop.lhs->str(false));
		str.append(" ");
		str.append(bop.rhs->str(false));
		str.append(")");
	}

	if (type == NodeType::nodeEmpty)
	{
		str.append("null");
	}



	if (endline) {str.push_back('\n');}
	return str;
}