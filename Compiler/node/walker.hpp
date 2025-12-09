#include "node.hpp"

#pragma once


class CtNodeWalker
{
	public:

	void walk(CtNode::Base* Ctnode);

	virtual void handleRoot(CtNode::RootProgram *Ctnode) = 0;
	virtual void handleSource(CtNode::Source *Ctnode) = 0;

	virtual void handleFunction(CtNode::Function *Ctnode) = 0;

	virtual void handleDeclaration(CtNode::Declaration *Ctnode) = 0;
	virtual void handleAssignment(CtNode::Assignment *Ctnode) = 0;

	virtual void handleInt(CtNode::Int *Ctnode) = 0;
	virtual void handleFloat(CtNode::Float *Ctnode) = 0;
	virtual void handleBinaryOp(CtNode::BinaryOp *Ctnode) = 0;
	virtual void handleIdentifier(CtNode::Identifier *Ctnode) = 0;
	virtual void handleFunctionCall(CtNode::FunctionCall *Ctnode) = 0;
};


class CtNodePrinter: public CtNodeWalker
{
	int indent = 0;
	void printIndent();
	
	public:

	void reset();

	void handleRoot(CtNode::RootProgram *Ctnode);
	void handleSource(CtNode::Source *Ctnode);

	void handleFunction(CtNode::Function *Ctnode);

	void handleDeclaration(CtNode::Declaration *Ctnode);
	void handleAssignment(CtNode::Assignment *Ctnode);

	void handleInt(CtNode::Int *Ctnode);
	void handleFloat(CtNode::Float *Ctnode);
	void handleBinaryOp(CtNode::BinaryOp *Ctnode);
	void handleIdentifier(CtNode::Identifier *Ctnode);
	void handleFunctionCall(CtNode::FunctionCall *Ctnode);
};