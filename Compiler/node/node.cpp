#include "node.hpp"


CtNode::RootProgram::~RootProgram()
{
	delete this->src;
}


CtNode::Source::~Source()
{
	for (auto func: this->functions)
	{
		delete func.second;
	}
}


CtNode::Function::~Function()
{
	delete this->name;
	
	for (auto para: this->parameters) {delete para;}
	for (auto stmt: this->statements) {delete stmt;}
}


CtNode::Declaration::~Declaration()
{
	delete this->type;
	delete this->name;
}


CtNode::Assignment::~Assignment()
{
	delete this->value;
	delete this->name;
}


CtNode::ExprStatment::~ExprStatment()
{
	delete this->expr;
}


CtNode::BinaryOp::~BinaryOp()
{
	delete this->left;
	delete this->right;
}


CtNode::FunctionCall::~FunctionCall()
{
	delete this->name;
	for (auto arg: this->args) {delete arg;}
}