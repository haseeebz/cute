#include <iostream>
#include <ostream>

#include "node.hpp"


void CtNodeWalker::walk(CtNode::Base *node) {

  if (!node) {
    std::cout << "Invalid Node! Node pointer is Null!" << std::endl;
    return;
  }

  switch (node->nt) {

  case CtNodeType::RootProgram:
    handleRoot(static_cast<CtNode::RootProgram *>(node));
    break;

  case CtNodeType::Source:
    handleSource(static_cast<CtNode::Source *>(node));
    break;

  case CtNodeType::Function:
    handleFunction(static_cast<CtNode::Function *>(node));
    break;

  case CtNodeType::Declaration:
    handleDeclaration(static_cast<CtNode::Declaration *>(node));
    break;

  case CtNodeType::Assignment:
    handleAssignment(static_cast<CtNode::Assignment *>(node));
    break;

  case CtNodeType::ExprStatement:
    walk(static_cast<CtNode::ExprStatment *>(node)->expr);
    break;

  case CtNodeType::Int:
    handleInt(static_cast<CtNode::Int *>(node));
    break;

  case CtNodeType::Float:
    handleFloat(static_cast<CtNode::Float *>(node));
    break;

  case CtNodeType::Identifier:
    handleIdentifier(static_cast<CtNode::Identifier *>(node));
    break;

  case CtNodeType::BinaryOp:
    handleBinaryOp(static_cast<CtNode::BinaryOp *>(node));
    break;

  case CtNodeType::FunctionCall:
    handleFunctionCall(static_cast<CtNode::FunctionCall *>(node));
    break;

  default:
    std::cout << "Undefined node passed to NodeWalker::walk" << std::endl;
    break;
  }
}


void CtNodePrinter::reset()
{
	this->indent = 0;
}


void CtNodePrinter::printIndent()
{
	for (int i = 0; i < this->indent; i++)
	{
		std::cout << "  ";
	}
}


void CtNodePrinter::handleRoot(CtNode::RootProgram *node)
{
	std::cout << "(Root Node)\n";

	this->walk(node->src);
}

void CtNodePrinter::handleSource(CtNode::Source *node)
{
	std::cout << "(Source Node)\n";
	std::cout << "Function Count: " << node->functions.size() << "\n\n";

	for (auto func: node->functions)
	{
		this->walk(func);
	}
}


void CtNodePrinter::handleFunction(CtNode::Function *node)
{
	std::cout << "(Function Node)\n";
	std::cout << "Function Identifier: " << node->name->val << "\n";
	std::cout << "Parameters: \n";
	
	for (int i = 0; i < node->parameters.size(); i++)
	{
		std::cout << i << ": ";
		this->walk(node->parameters[i]);
	}

	std::cout << "\nStatements:\n\n";

	for (int i = 0; i < node->statements.size(); i++)
	{
		this->walk(node->statements[i]);
		std::cout << ";\n";
	}
}

void CtNodePrinter::handleDeclaration(CtNode::Declaration *node)
{
	this->printIndent();
	std::cout << "(Declaration name= " << node->name->val << " type= " << node->type->val << ")\n";
}

void CtNodePrinter::handleAssignment(CtNode::Assignment *node)
{
	this->printIndent();
	std::cout << "(Assignement \n";

	this->indent++;

	this->printIndent();
	std::cout <<  " name= " << node->name->val;
	std::cout <<  " value=\n";

	this->walk(node->value);

	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}


void CtNodePrinter::handleInt(CtNode::Int *node)
{
	this->printIndent();
	std::cout << "(Int " << node->raw << ")\n";
}

void CtNodePrinter::handleFloat(CtNode::Float *node)
{
	this->printIndent();
	std::cout << "(Float " << node->raw << ")\n";
}

void CtNodePrinter::handleBinaryOp(CtNode::BinaryOp *node)
{
	this->printIndent();
	std::cout << "(BinaryOp \n";

	this->indent++;

	this->printIndent();
	switch (node->op)
	{
        case CtNode::BinaryOp::Type::Add: std::cout << "+\n"; break;
        case CtNode::BinaryOp::Type::Sub: std::cout << "-\n"; break;
        case CtNode::BinaryOp::Type::Mul: std::cout << "*\n"; break;
        case CtNode::BinaryOp::Type::Div: std::cout << "/\n"; break;
    }
	
	this->walk(node->left);
	this->walk(node->right);

	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}


void CtNodePrinter::handleIdentifier(CtNode::Identifier *node)
{
	this->printIndent();
	std::cout << "(Identifier " << node->val << ")\n";
}


void CtNodePrinter::handleFunctionCall(CtNode::FunctionCall *node)
{
	this->printIndent();
	std::cout << "(FunctionCall name:" << node->name->val << " args:\n";
	this->indent++; 
	for (auto args: node->args) {this->walk(args);}
	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}
