#include "CuteByte.h"
#include "../node/node.hpp"

#pragma once

class CtEmitter : CtNodeWalker
{
	ctProgramImage img;
	std::vector<ctInstrSize> instrs;
	std::map<std::string, int> variables;

	void write(std::string outfile);

	void handleRoot(CtNode::RootProgram *node);
	void handleSource(CtNode::Source *node);

	void handleFunction(CtNode::Function *node);

	void handleDeclaration(CtNode::Declaration *node);
	void handleAssignment(CtNode::Assignment *node);

	void handleInt(CtNode::Int *node);
	void handleFloat(CtNode::Float *node) {};
	void handleBinaryOp(CtNode::BinaryOp *node);
	void handleIdentifier(CtNode::Identifier *node);
	void handleFunctionCall(CtNode::FunctionCall *node) {};
	void handleTypeCast(CtNode::TypeCast *node) {};

	public:

	void emit(CtNode::RootProgram *root, std::string outfile);
};