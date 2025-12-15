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
	for (auto para: this->parameters) {delete para;}
	for (auto stmt: this->statements) {delete stmt;}
}


CtNode::Declaration::~Declaration()
{
}


CtNode::Assignment::~Assignment()
{
	delete this->value;
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
	for (auto arg: this->args) {delete arg;}
}