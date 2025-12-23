#include "../node/node.hpp"
#include "../spec/scope.hpp"

#pragma once


class CtNameResolver: public CtNodeWalker
{	
	CtNode::RootProgram* root;

	CtScope::Scope* current_scope;

	void handleRoot(CtNode::RootProgram *node);
	void handleSource(CtNode::Source *node);

	void handleFunction(CtNode::Function *node);

	void handleDeclaration(CtNode::Declaration *node);
	void handleOut(CtNode::Out *node);
	void handleLoop(CtNode::Loop *node);

	void handleInt(CtNode::Int *node);
	void handleFloat(CtNode::Float *node);
	void handleBool(CtNode::Bool *node);
	void handleBinaryOp(CtNode::BinaryOp *node);
	void handleIdentifier(CtNode::Identifier *node);
	void handleFunctionCall(CtNode::FunctionCall *node);
	void handleAssignment(CtNode::Assignment *node);
	void handleTypeCast(CtNode::TypeCast *node);

	public:

	CtNode::RootProgram* analyze(CtNode::RootProgram* root);
};