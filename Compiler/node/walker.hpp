#include "node.hpp"

#pragma once


class NodeWalker
{
	public:

	void walk(Node::Base* node);

	virtual void handleRoot(Node::RootProgram *node) = 0;
	virtual void handleSource(Node::Source *node) = 0;

	virtual void handleFunction(Node::Function *node) = 0;

	virtual void handleDeclaration(Node::Declaration *node) = 0;
	virtual void handleAssignment(Node::Assignment *node) = 0;

	virtual void handleInt(Node::Int *node) = 0;
	virtual void handleFloat(Node::Float *node) = 0;
	virtual void handleBinaryOp(Node::BinaryOp *node) = 0;
	virtual void handleIdentifier(Node::Identifier *node) = 0;
	virtual void handleFunctionCall(Node::FunctionCall *node) = 0;
};


class NodePrinter: public NodeWalker
{
	int indent = 0;
	void printIndent();
	
	public:

	void reset();

	void handleRoot(Node::RootProgram *node);
	void handleSource(Node::Source *node);

	void handleFunction(Node::Function *node);

	void handleDeclaration(Node::Declaration *node);
	void handleAssignment(Node::Assignment *node);

	void handleInt(Node::Int *node);
	void handleFloat(Node::Float *node);
	void handleBinaryOp(Node::BinaryOp *node);
	void handleIdentifier(Node::Identifier *node);
	void handleFunctionCall(Node::FunctionCall *node);
};