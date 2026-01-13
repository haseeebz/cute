#include "node.hpp"



CtGenNode::Function::~Function() 
{
    for (auto* param : parameters) delete param;
    delete body;
}


CtGenNode::Struct::~Struct() 
{
    for (auto* field : fields) delete field;
}


CtGenNode::StmtBlock::~StmtBlock() 
{
    for (auto* stmt : body) delete stmt;
}


CtGenNode::Assignment::~Assignment() 
{
    delete val;
}


CtGenNode::Declaration::~Declaration() 
{
    delete val;
}


CtGenNode::ExprStmt::~ExprStmt() 
{
    delete expr;
}


CtGenNode::While::~While() 
{
    delete condition;
    delete body;
}


CtGenNode::For::~For() 
{
    delete init;
    delete condition;
    delete step;
    delete body;
}


CtGenNode::If::~If() 
{
    delete condition;
    delete then_block;
    delete else_block;
}


CtGenNode::BinaryOp::~BinaryOp() 
{
    delete lhs;
    delete rhs;
}


CtGenNode::UnaryOp::~UnaryOp() 
{
    delete expr;
}


CtGenNode::Call::~Call() 
{
    for (auto* arg : args) delete arg;
}
