#include "CuteByte.h"
#include "../node/node.hpp"

#include <iostream>
#include <string>

#include "emitter.hpp"


static inline std::map<std::string, CtCodeGen::OpType> op_type_map =
{
    {"i32", CtCodeGen::OpType::i32},
    {"i64", CtCodeGen::OpType::i64},
    {"u32", CtCodeGen::OpType::u32},
    {"u64", CtCodeGen::OpType::u64},
    {"f32", CtCodeGen::OpType::f32},
    {"f64", CtCodeGen::OpType::f64},
};


CtCodeGen::Program* CtEmitter::emit(CtNode::RootProgram *root)
{
	this->program = new CtCodeGen::Program();
	this->walk(root);
	return this->program;
}


void CtEmitter::handleRoot(CtNode::RootProgram *node)
{
	this->walk(node->src);
}


void CtEmitter::handleSource(CtNode::Source *node)
{
	this->walk(node->functions["main"]);
}


void CtEmitter::handleFunction(CtNode::Function *node)
{
	auto* func = new CtCodeGen::Function();
	this->current_function = func;
	this->program->functions[0] = func;

	for (auto stmt: node->statements)
	{
		this->walk(stmt);
	}	

	func->id = 0;
	func->locals_count = this->variables.size();
	func->arg_count = 0;
}


void CtEmitter::handleInt(CtNode::Int *node)
{
	int i = std::stoi(node->raw);
	this->current_function->units.push_back(new CtCodeGen::LoadConstOp(i));
}


void CtEmitter::handleFloat(CtNode::Float *node)
{
	float f = std::stof(node->raw);
	this->current_function->units.push_back(new CtCodeGen::LoadConstOp(f));
}


void CtEmitter::handleBinaryOp(CtNode::BinaryOp *node)
{
	this->walk(node->left);
	this->walk(node->right);

	CtCodeGen::Unit* op;

	switch (node->op)
	{
		case CtLang::Symbol::Plus:       op = new CtCodeGen::AddOp(op_type_map[node->result_type]); break;
		case CtLang::Symbol::Minus:      op = new CtCodeGen::SubOp(op_type_map[node->result_type]); break;
		case CtLang::Symbol::Star:       op = new CtCodeGen::MulOp(op_type_map[node->result_type]); break;
		case CtLang::Symbol::Slash:      op = new CtCodeGen::DivOp(op_type_map[node->result_type]); break;
		case CtLang::Symbol::Percentage: op = new CtCodeGen::ModOp(op_type_map[node->result_type]); break;
	}

	this->current_function->units.push_back(op);
}


void CtEmitter::handleDeclaration(CtNode::Declaration *node)
{
	this->variables[node->name] = this->variables.size();
}


void CtEmitter::handleOut(CtNode::Out *node)
{
	this->walk(node->expr);

	static std::map<std::string, int> format_specfier =
	{
		{"i32", 2},
		{"i64", 3},
		{"u32", 4},
		{"u64", 5},
		{"f32", 6},
		{"f64", 7},
	};

	this->current_function->units.push_back(new CtCodeGen::Out(format_specfier[node->expr->result_type]));
}


void CtEmitter::handleAssignment(CtNode::Assignment *node)
{
	this->walk(node->value);
	this->current_function->units.push_back(
		new CtCodeGen::StoreOp(op_type_map[node->result_type], this->variables[node->name->val])
	);
}


void CtEmitter::handleIdentifier(CtNode::Identifier *node)
{
	this->current_function->units.push_back(
		new CtCodeGen::LoadOp(op_type_map[node->result_type], this->variables[node->val])
	);
}


void CtEmitter::handleTypeCast(CtNode::TypeCast *node)
{
	this->walk(node->expr);
	this->current_function->units.push_back(
		new CtCodeGen::TypeCastOp(op_type_map[node->expr->result_type], op_type_map[node->to_type])
	);
}
