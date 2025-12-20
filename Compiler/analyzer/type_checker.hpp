#include "../node/node.hpp"
#include "../spec/scope.hpp"
#include "../spec/spec.hpp"

#include "map"
#include <string>

#pragma once


static inline std::map<std::string, CtSpec::TypeInfo*> primitiveTypes =
{
	{"int",    new CtSpec::TypeInfo("int", CtSpec::PrimitiveT::Int)},
	{"uint",   new CtSpec::TypeInfo("uint", CtSpec::PrimitiveT::UInt)},
	{"float",  new CtSpec::TypeInfo("float", CtSpec::PrimitiveT::Float)},
	{"bool",   new CtSpec::TypeInfo("bool", CtSpec::PrimitiveT::Bool)},
};


class CtTypeChecker: public CtNodeWalker
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
	void handleBinaryOp(CtNode::BinaryOp *node);
	void handleIdentifier(CtNode::Identifier *node);
	void handleFunctionCall(CtNode::FunctionCall *node);
	void handleAssignment(CtNode::Assignment *node);
	void handleTypeCast(CtNode::TypeCast *node);
	
	public:

	CtNode::RootProgram* analyze(CtNode::RootProgram* root);
};