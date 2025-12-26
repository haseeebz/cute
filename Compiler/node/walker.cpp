#include <iostream>
#include <ostream>


#include "../spec/spec.hpp"
#include "node.hpp"


void CtNodeWalker::walk(CtNode::Base *node) {

	if (!node) {
	std::cout << "(Null Node)" << std::endl;
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

	case CtNodeType::StmtBlock:
	handleStmtBlock(static_cast<CtNode::StmtBlock *>(node));
	break;

	case CtNodeType::Declaration:
	handleDeclaration(static_cast<CtNode::Declaration *>(node));
	break;

	case CtNodeType::Out:
	handleOut(static_cast<CtNode::Out *>(node));
	break;

	case CtNodeType::ExprStatement:
	walk(static_cast<CtNode::ExprStatment *>(node)->expr);
	break;

	case CtNodeType::Loop:
	handleLoop(static_cast<CtNode::Loop *>(node));
	break;

	case CtNodeType::While:
	handleWhile(static_cast<CtNode::While *>(node));
	break;

	case CtNodeType::For:
	handleFor(static_cast<CtNode::For *>(node));
	break;

	case CtNodeType::If:
	handleIf(static_cast<CtNode::If *>(node));
	break;

	case CtNodeType::Int:
	handleInt(static_cast<CtNode::Int *>(node));
	break;

	case CtNodeType::Float:
	handleFloat(static_cast<CtNode::Float *>(node));
	break;

	case CtNodeType::Bool:
	handleBool(static_cast<CtNode::Bool *>(node));
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

	case CtNodeType::Assignment:
	handleAssignment(static_cast<CtNode::Assignment *>(node));
	break;

	case CtNodeType::TypeCast:
	handleTypeCast(static_cast<CtNode::TypeCast *>(node));
	break;

	default:
	std::cout << "(Undefined Node)" << std::endl;
	break;
	}
}


// Printer Implementation. Mainly used for debugging.

void CtNodePrinter::print(CtNode::Base *node)
{
	this->indent = 0;
	this->walk(node);
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
		this->walk(func.second);
	}
}


void CtNodePrinter::handleFunction(CtNode::Function *node)
{
	std::cout << "(Function Node)\n";
	std::cout << "Function Identifier: " << node->name << "\n";
	std::cout << "Parameters: \n";
	
	for (uint i = 0; i < node->parameters.size(); i++)
	{
		std::cout << i << ": ";
		this->walk(node->parameters[i]);
	}

	std::cout << "\nStatements:\n\n";
	this->indent++;

	this->walk(node->block);

	this->indent--;
}

void CtNodePrinter::handleStmtBlock(CtNode::StmtBlock *node)
{
	for (auto stmt: node->stmts)
	{
		this->printIndent();
		this->walk(stmt);
		std::cout << "\n";
	}
}


void CtNodePrinter::handleDeclaration(CtNode::Declaration *node)
{
	this->printIndent();
	std::cout << "(Declaration name= " << node->name << " type= " << node->type << "\n";
	if (!node->assignment) {return;}

	this->printIndent();
	this->indent++;
	std::cout << "assignment=\n";
	this->walk(node->assignment);
	this->indent--;
	this->printIndent();
	std::cout<< ")\n";
}


void CtNodePrinter::handleOut(CtNode::Out *node)
{
	this->printIndent();
	std::cout << "(Out expr=\n";
	this->indent++;
	this->walk(node->expr);
	this->indent--;
	this->printIndent();
	std::cout << ")\n";
}


void CtNodePrinter::handleLoop(CtNode::Loop *node)
{
	this->printIndent();
	std::cout << "(Loop statements=\n";
	this->indent++;
	this->walk(node->block);
	this->indent--;
	this->printIndent();
	std::cout << ")\n";
}

void CtNodePrinter::handleWhile(CtNode::While *node)
{
	this->printIndent();
	std::cout << "(While\n";
	this->indent++;
	this->printIndent();
	std::cout << "condition = \n";
	this->walk(node->condition);
	this->printIndent();
	std::cout << "statements = \n";
	this->walk(node->block);
	this->indent--;
	this->printIndent();
	std::cout << ")\n";
}

void CtNodePrinter::handleFor(CtNode::For *node)
{
	this->printIndent();
	std::cout << "(For\n";
	this->indent++;
	this->printIndent();
	std::cout << "init = \n";
	this->walk(node->init);
	this->printIndent();
	std::cout << "condition = \n";
	this->walk(node->condition);
	this->printIndent();
	std::cout << "step = \n";
	this->walk(node->step);
	this->printIndent();
	std::cout << "statements = \n";
	this->walk(node->block);
	this->indent--;
	this->printIndent();
	std::cout << ")\n";
}


void CtNodePrinter::handleIf(CtNode::If *node)
{
	this->printIndent();
	std::cout << "(If condition=\n";
	this->indent++;
	this->walk(node->condition);
	this->printIndent();
	std::cout << "then=\n";
	this->walk(node->then_block);
	this->printIndent();
	std::cout << "else=\n";
	if (node->else_stmt) {this->walk(node->else_stmt);}
	this->indent--;
	this->printIndent();
	std::cout << ")\n";
};

void CtNodePrinter::handleAssignment(CtNode::Assignment *node)
{
	this->printIndent();
	std::cout << "(Assignement \n";

	this->indent++;

	this->printIndent();
	std::cout <<  " variable= " << node->name->val;
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

void CtNodePrinter::handleBool(CtNode::Bool *node)
{
	this->printIndent();
	std::cout << "(Bool " << node->val << ")\n";
}

void CtNodePrinter::handleBinaryOp(CtNode::BinaryOp *node)
{
	this->printIndent();
	std::cout << "(BinaryOp \n";

	this->indent++;

	this->printIndent();
	switch (node->op)
	{
        case CtSpec::BinaryOpType::Add:  std::cout << "+\n"; break;
        case CtSpec::BinaryOpType::Sub:  std::cout << "-\n"; break;
        case CtSpec::BinaryOpType::Mul:  std::cout << "*\n"; break;
        case CtSpec::BinaryOpType::Div:  std::cout << "/\n"; break;
		case CtSpec::BinaryOpType::Mod:  std::cout << "%\n"; break;
		default:					std::cout << "u\n"; break;
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
	std::cout << "(FunctionCall name:" << node->name << " args:\n";
	this->indent++; 
	for (auto args: node->args) {this->walk(args);}
	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}


void CtNodePrinter::handleTypeCast(CtNode::TypeCast *node)
{
	this->printIndent();
	std::cout << "(TypeCast type:" << node->to_type << " expr:\n";
	this->indent++; 
	this->walk(node->expr);
	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}
