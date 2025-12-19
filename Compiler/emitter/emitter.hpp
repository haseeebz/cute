#include "CuteByte.h"
#include "../node/node.hpp"

#include "../bytecode/gen.hpp"

#pragma once

class CtEmitter : CtNodeWalker
{
	CtCodeGen::Program* program;
	CtCodeGen::Function* current_function;
	
	std::map<std::string, uint> variables;

	void handleRoot(CtNode::RootProgram *node);
	void handleSource(CtNode::Source *node);

	void handleFunction(CtNode::Function *node);

	void handleDeclaration(CtNode::Declaration *node);
	void handleOut(CtNode::Out *node);

	
	void handleInt(CtNode::Int *node);
	void handleFloat(CtNode::Float *node);
	void handleBinaryOp(CtNode::BinaryOp *node);
	void handleIdentifier(CtNode::Identifier *node);
	void handleFunctionCall(CtNode::FunctionCall *node) {};
	void handleAssignment(CtNode::Assignment *node);
	void handleTypeCast(CtNode::TypeCast *node);

	public:

	CtCodeGen::Program* emit(CtNode::RootProgram *root);
};