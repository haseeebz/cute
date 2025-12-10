#include "CuteByte.h"
#include "../node/node.hpp"

#pragma once

class CtEmitter : CtNodeWalker
{
	ctProgramImage img;
	std::vector<ctInstrSize> instrs;

	void write(std::string outfile);

	void handleRoot(CtNode::RootProgram *Ctnode);
	void handleSource(CtNode::Source *Ctnode);

	void handleFunction(CtNode::Function *Ctnode);

	void handleDeclaration(CtNode::Declaration *Ctnode) {};
	void handleAssignment(CtNode::Assignment *Ctnode) {};

	void handleInt(CtNode::Int *Ctnode);
	void handleFloat(CtNode::Float *Ctnode) {};
	void handleBinaryOp(CtNode::BinaryOp *Ctnode);
	void handleIdentifier(CtNode::Identifier *Ctnode) {};
	void handleFunctionCall(CtNode::FunctionCall *Ctnode) {};

	public:


	void emit(CtNode::RootProgram *root, std::string outfile);
};