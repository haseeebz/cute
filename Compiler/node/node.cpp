#include "node.hpp"


Node::RootProgram::~RootProgram()
{
	delete this->src;
}


Node::Source::~Source()
{
	for (auto func: this->functions)
	{
		delete func;
	}
}


Node::Function::~Function()
{
	delete this->name;
	
	for (auto para: this->parameters) {delete para;}
	for (auto stmt: this->statements) {delete stmt;}
}


Node::Declaration::~Declaration()
{
	delete this->type;
	delete this->name;
}


Node::Assignment::~Assignment()
{
	delete this->value;
	delete this->name;
}


Node::ExprStatment::~ExprStatment()
{
	delete this->expr;
}


Node::BinaryOp::~BinaryOp()
{
	delete this->left;
	delete this->right;
}


Node::FunctionCall::~FunctionCall()
{
	delete this->name;
	for (auto arg: this->args) {delete arg;}
}