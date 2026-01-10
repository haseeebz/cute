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
	delete this->block;
}


CtNode::StmtBlock::~StmtBlock()
{
	for (auto stmt: this->stmts)
	{
		delete stmt;
	}
}


CtNode::Out::~Out()
{
	delete this->expr;
}


CtNode::Declaration::~Declaration()
{
	delete this->val;
}

CtNode::Loop::~Loop()
{
	delete this->block;
}

CtNode::If::~If()
{
	delete this->condition;
	delete this->then_block;
	delete this->else_stmt;
}


CtNode::Assignment::~Assignment()
{
	delete this->name;
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


CtNode::TypeCast::~TypeCast()
{
	delete this->expr;
}

