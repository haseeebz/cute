#include "../node/node.hpp"

#include <iostream>
#include <string>

#include "../spec/spec.hpp"
#include "emitter.hpp"


static inline std::map<CtSpec::PrimitiveT, CtCodeGen::OpType> op_type_map =
{
    {CtSpec::PrimitiveT::I32, CtCodeGen::OpType::i32},
    {CtSpec::PrimitiveT::I64, CtCodeGen::OpType::i64},
    {CtSpec::PrimitiveT::U32, CtCodeGen::OpType::u32},
    {CtSpec::PrimitiveT::U64, CtCodeGen::OpType::u64},
    {CtSpec::PrimitiveT::F32, CtCodeGen::OpType::f32},
    {CtSpec::PrimitiveT::F64, CtCodeGen::OpType::f64},
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
	this->current_function->units.push_back(new CtCodeGen::LoadConstOp(node->val.i64));
}


void CtEmitter::handleFloat(CtNode::Float *node)
{
	this->current_function->units.push_back(new CtCodeGen::LoadConstOp(node->val.f64));
}


void CtEmitter::handleBinaryOp(CtNode::BinaryOp *node)
{
	this->walk(node->left);
	this->walk(node->right);

	CtCodeGen::Unit* op;

	switch (node->op)
	{
		case CtSpec::BinaryOpType::Add:       op = new CtCodeGen::AddOp(op_type_map[node->expr_type->primitive]); break;
		case CtSpec::BinaryOpType::Sub:       op = new CtCodeGen::SubOp(op_type_map[node->expr_type->primitive]); break;
		case CtSpec::BinaryOpType::Mul:       op = new CtCodeGen::MulOp(op_type_map[node->expr_type->primitive]); break;
		case CtSpec::BinaryOpType::Div:       op = new CtCodeGen::DivOp(op_type_map[node->expr_type->primitive]); break;
		case CtSpec::BinaryOpType::Mod:       op = new CtCodeGen::ModOp(op_type_map[node->expr_type->primitive]); break;
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

	static std::map<CtSpec::PrimitiveT, int> format_specfier =
	{
		{CtSpec::PrimitiveT::I32, 2},
		{CtSpec::PrimitiveT::I64, 3},
		{CtSpec::PrimitiveT::U32, 4},
		{CtSpec::PrimitiveT::U64, 5},
		{CtSpec::PrimitiveT::F32, 6},
		{CtSpec::PrimitiveT::F64, 7},
	};

	this->current_function->units.push_back(new CtCodeGen::Out(format_specfier[node->expr->expr_type->primitive]));
}


void CtEmitter::handleAssignment(CtNode::Assignment *node)
{
	this->walk(node->value);
	this->current_function->units.push_back(
		new CtCodeGen::StoreOp(op_type_map[node->expr_type->primitive], this->variables[node->name->val])
	);
}


void CtEmitter::handleIdentifier(CtNode::Identifier *node)
{
	this->current_function->units.push_back(
		new CtCodeGen::LoadOp(op_type_map[node->expr_type->primitive], this->variables[node->val])
	);
}


void CtEmitter::handleTypeCast(CtNode::TypeCast *node)
{
	std::cout << node->expr->expr_type->name << " " << node->expr_type->name << std::endl; 
	this->walk(node->expr);
	this->current_function->units.push_back(
		new CtCodeGen::TypeCastOp(op_type_map[node->expr->expr_type->primitive], op_type_map[node->expr_type->primitive])
	);
}
