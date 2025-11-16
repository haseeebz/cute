#include <iostream>
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

	depth++;
	printDepth();
	std::cout << '[' << node->op << ']' << "\n";
	node->lhs->accept(this);
	node->rhs->accept(this);
	depth--;

	printDepth();
	std::cout << ")\n";
}


void PrintVisitor::visit(ctIdentifierNode* node) 
{
	printDepth();

	std::cout << "Identifier(" << node->val << ")\n";
}


void PrintVisitor::visit(ctIdentifierListNode* node)
{
	printDepth();

	std::cout << "IdentifierList(";
	for (ctIdentifierNode idf: node->nodes)
	{
		std::cout << idf.val << " ";
	}
	std::cout << ")\n";
}


void PrintVisitor::visit(ctStmtNode* node)
{
	printDepth();

	std::cout << "Statement[\n";
	depth++;
	node->accept(this);
	depth--;
	std::cout << "]\n";

}


void PrintVisitor::visit(ctProgramNode* node)
{
	printDepth();

	std::cout << "--Program Node--\n";
	
	for (ctStmtNode& child: node->stmts)
	{
		child.accept(this);
	}
}