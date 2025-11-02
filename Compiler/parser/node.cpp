#include "node.hpp"

Node::~Node()
{
	if (type == NodeType::nodeBinaryOp)
	{
		delete bop.lhs;
		delete bop.rhs;
	}
}