#include "CuteByte.h"
#include "../node/node.hpp"

#include "../bytecode/gen.hpp"

#pragma once

using VariableMap = std::map<std::string, uint>;

class CtEmitter : CtNodeWalker
{
	CtCodeGen::Program* program;
	CtCodeGen::Function* current_function;
	
	std::vector<VariableMap> variables;
	uint global_var_count = 0;
	CtScope* current_scope;

	void handleRoot(CtNode::RootProgram *node);
	void handleSource(CtNode::Source *node);

	void handleFunction(CtNode::Function *node);

	void handleStmtBlock(CtNode::StmtBlock *node);
	void handleDeclaration(CtNode::Declaration *node);
	void handleOut(CtNode::Out *node);
	void handleIf(CtNode::If* node);
	void handleLoop(CtNode::Loop *node);
	void handleWhile(CtNode::While *node);
	void handleFor(CtNode::For *node);

	
	void handleInt(CtNode::Int *node);
	void handleFloat(CtNode::Float *node);
	void handleBool(CtNode::Bool *node);
	void handleBinaryOp(CtNode::BinaryOp *node);
	void handleIdentifier(CtNode::Identifier *node);
	void handleFunctionCall(CtNode::FunctionCall *node) {};
	void handleAssignment(CtNode::Assignment *node);
	void handleTypeCast(CtNode::TypeCast *node);

	public:

	CtCodeGen::Program* emit(CtNode::RootProgram *root);
};