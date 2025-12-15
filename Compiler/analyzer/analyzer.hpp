#include "../node/node.hpp"
#include "../spec/types.hpp"

#pragma once


class CtAnalyzer: public CtNodeWalker
{
	std::map<std::string, CtTypes::TypeInfo> typeMap;
	
	void handleRoot(CtNode::RootProgram *node);
	void handleSource(CtNode::Source *node);

	void handleFunction(CtNode::Function *node);

	void handleDeclaration(CtNode::Declaration *node);
	void handleAssignment(CtNode::Assignment *node);

	void handleInt(CtNode::Int *node);
	void handleFloat(CtNode::Float *node);
	void handleBinaryOp(CtNode::BinaryOp *node);
	void handleIdentifier(CtNode::Identifier *node);
	void handleFunctionCall(CtNode::FunctionCall *node);
	
	public:

	CtNode::RootProgram* analyze(CtNode::RootProgram* root);
};