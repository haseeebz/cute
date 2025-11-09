#include <iostream>
#include <string>
#include "node.hpp"


void PrintVisitor::printDepth()
{
	for (uint i = 0; i < depth; i++)
	{
		std::cout << "	";
	}
}


void PrintVisitor::visit(ctIntNode* node) 
{
	printDepth();

	std::cout << "Int(" << node->raw << ")\n";
}


void PrintVisitor::visit(ctFloatNode* node)
{
	printDepth();

	std::cout << "Float(" << node->raw << ")\n";
}


void PrintVisitor::visit(ctBinaryOpNode* node)
{
	printDepth();
	std::cout << "BinaryOp(\n";

	printDepth();
	std::cout << node->op << "\n";

	depth++;
	node->lhs->accept(this);
	node->rhs->accept(this);
	depth--;
}


void PrintVisitor::visit(ctIdentifierNode* node) 
{
	printDepth();

	std::cout << "Identifier(" << node->val << ")\n";
}
