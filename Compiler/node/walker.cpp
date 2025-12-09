#include <iostream>
#include <ostream>

#include "node.hpp"
#include "walker.hpp"

void NodeWalker::walk(Node::Base *node) {

  if (!node) {
    std::cout << "Invalid Node! Node pointer is Null!" << std::endl;
    return;
  }

  switch (node->nt) {

  case NodeType::RootProgram:
    handleRoot(static_cast<Node::RootProgram *>(node));
    break;

  case NodeType::Source:
    handleSource(static_cast<Node::Source *>(node));
    break;

  case NodeType::Function:
    handleFunction(static_cast<Node::Function *>(node));
    break;

  case NodeType::Declaration:
    handleDeclaration(static_cast<Node::Declaration *>(node));
    break;

  case NodeType::Assignment:
    handleAssignment(static_cast<Node::Assignment *>(node));
    break;

  case NodeType::ExprStatement:
    walk(static_cast<Node::ExprStatment *>(node)->expr);
    break;

  case NodeType::Int:
    handleInt(static_cast<Node::Int *>(node));
    break;

  case NodeType::Float:
    handleFloat(static_cast<Node::Float *>(node));
    break;

  case NodeType::Identifier:
    handleIdentifier(static_cast<Node::Identifier *>(node));
    break;

  case NodeType::BinaryOp:
    handleBinaryOp(static_cast<Node::BinaryOp *>(node));
    break;

  case NodeType::FunctionCall:
    handleFunctionCall(static_cast<Node::FunctionCall *>(node));
    break;

  default:
    std::cout << "Undefined node passed to NodeWalker::walk" << std::endl;
    break;
  }
}


void NodePrinter::reset()
{
	this->indent = 0;
}


void NodePrinter::printIndent()
{
	for (int i = 0; i < this->indent; i++)
	{
		std::cout << "  ";
	}
}


void NodePrinter::handleRoot(Node::RootProgram *node)
{
	std::cout << "(Root Node)\n";

	this->walk(node->src);
}

void NodePrinter::handleSource(Node::Source *node)
{
	std::cout << "(Source Node)\n";
	std::cout << "Function Count: " << node->functions.size() << "\n\n";

	for (auto func: node->functions)
	{
		this->walk(func);
	}
}


void NodePrinter::handleFunction(Node::Function *node)
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

void NodePrinter::handleDeclaration(Node::Declaration *node)
{
	this->printIndent();
	std::cout << "(Declaration name= " << node->name->val << " type= " << node->type->val << ")\n";
}

void NodePrinter::handleAssignment(Node::Assignment *node)
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


void NodePrinter::handleInt(Node::Int *node)
{
	this->printIndent();
	std::cout << "(Int " << node->raw << ")\n";
}

void NodePrinter::handleFloat(Node::Float *node)
{
	this->printIndent();
	std::cout << "(Float " << node->raw << ")\n";
}

void NodePrinter::handleBinaryOp(Node::BinaryOp *node)
{
	this->printIndent();
	std::cout << "(BinaryOp \n";

	this->indent++;

	this->printIndent();
	switch (node->op)
	{
        case Node::BinaryOp::Type::Add: std::cout << "+\n"; break;
        case Node::BinaryOp::Type::Sub: std::cout << "-\n"; break;
        case Node::BinaryOp::Type::Mul: std::cout << "*\n"; break;
        case Node::BinaryOp::Type::Div: std::cout << "/\n"; break;
    }
	
	this->walk(node->left);
	this->walk(node->right);

	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}


void NodePrinter::handleIdentifier(Node::Identifier *node)
{
	this->printIndent();
	std::cout << "(Identifier " << node->val << ")\n";
}


void NodePrinter::handleFunctionCall(Node::FunctionCall *node)
{
	this->printIndent();
	std::cout << "(FunctionCall name:" << node->name->val << " args:\n";
	this->indent++; 
	for (auto args: node->args) {this->walk(args);}
	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}
