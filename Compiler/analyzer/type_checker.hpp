#include "../node/node.hpp"
#include "../spec/scope.hpp"
#include "../spec/spec.hpp"

#include "map"
#include <string>

#pragma once


static inline std::map<std::string, CtSpec::TypeInfo*> primitiveTypes =
{
	{"i32",  new CtSpec::TypeInfo("i32", CtSpec::PrimitiveT::I32)},
	{"i64",  new CtSpec::TypeInfo("i64", CtSpec::PrimitiveT::I64)},
	{"u32",  new CtSpec::TypeInfo("u32", CtSpec::PrimitiveT::U32)},
	{"u64",  new CtSpec::TypeInfo("u64", CtSpec::PrimitiveT::U64)},
	{"f32",  new CtSpec::TypeInfo("u32", CtSpec::PrimitiveT::F32)},
	{"f64",  new CtSpec::TypeInfo("f64", CtSpec::PrimitiveT::F64)},
	{"bool", new CtSpec::TypeInfo("bool", CtSpec::PrimitiveT::Bool)},
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