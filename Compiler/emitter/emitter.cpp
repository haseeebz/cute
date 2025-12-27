#include "../node/node.hpp"

#include <iostream>

#include "../spec/spec.hpp"
#include "emitter.hpp"


static inline std::map<CtSpec::PrimitiveT, CtCodeGen::OpType> op_type_map =
{
    {CtSpec::PrimitiveT::Int,   CtCodeGen::OpType::Int},
    {CtSpec::PrimitiveT::UInt,  CtCodeGen::OpType::UInt},
    {CtSpec::PrimitiveT::Float, CtCodeGen::OpType::Float},
	{CtSpec::PrimitiveT::Bool, CtCodeGen::OpType::Int}
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

	this->walk(node->block);

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


void CtEmitter::handleBool(CtNode::Bool *node)
{
	this->current_function->units.push_back(new CtCodeGen::LoadConstOp(int64_t(node->val)));
};


void CtEmitter::handleBinaryOp(CtNode::BinaryOp *node)
{
	this->walk(node->left);
	this->walk(node->right);

	CtCodeGen::Unit* op;

	using Bin = CtSpec::BinaryOpType;
	switch (node->op)
	{
		case Bin::Add:       
			op = new CtCodeGen::AddOp(op_type_map[node->expr_type->primitive]); break;
		case Bin::Sub:       
			op = new CtCodeGen::SubOp(op_type_map[node->expr_type->primitive]); break;
		case Bin::Mul:      
			op = new CtCodeGen::MulOp(op_type_map[node->expr_type->primitive]); break;
		case Bin::Div:      
			op = new CtCodeGen::DivOp(op_type_map[node->expr_type->primitive]); break;
		case Bin::Mod:       
			op = new CtCodeGen::ModOp(op_type_map[node->expr_type->primitive]); break;
		case Bin::Equal:     
			op = new CtCodeGen::CmpOp(op_type_map[node->expr_type->primitive], CtCodeGen::CmpType::Eq); break;
		case Bin::NotEqual:  
			op = new CtCodeGen::CmpOp(op_type_map[node->expr_type->primitive], CtCodeGen::CmpType::Ue); break;
		case Bin::Lesser:
			op = new CtCodeGen::CmpOp(op_type_map[node->expr_type->primitive], CtCodeGen::CmpType::Lt); break;
		case Bin::LesserEqual:
			op = new CtCodeGen::CmpOp(op_type_map[node->expr_type->primitive], CtCodeGen::CmpType::Le); break;
		case Bin::Greater:
			op = new CtCodeGen::CmpOp(op_type_map[node->expr_type->primitive], CtCodeGen::CmpType::Gt); break;
		case Bin::GreaterEqual:
			op = new CtCodeGen::CmpOp(op_type_map[node->expr_type->primitive], CtCodeGen::CmpType::Ge); break;	
		case Bin::BitShiftLeft: 
			op = new CtCodeGen::BitWiseOp(CtCodeGen::BitwiseOpType::LShift); break;
		case Bin::BitShiftRight:
			op = new CtCodeGen::BitWiseOp((op_type_map[node->expr_type->primitive] == CtCodeGen::OpType::Int ) ? CtCodeGen::BitwiseOpType::RaShift : CtCodeGen::BitwiseOpType::RShift); break; // ts is frying me
		case Bin::BitAnd:
			op = new CtCodeGen::BitWiseOp(CtCodeGen::BitwiseOpType::And); break;
		case Bin::BitOr:
			op = new CtCodeGen::BitWiseOp(CtCodeGen::BitwiseOpType::Or); break;
		case Bin::BitXor:
			op = new CtCodeGen::BitWiseOp(CtCodeGen::BitwiseOpType::Xor); break;
		case Bin::LogicAnd:
			op = new CtCodeGen::LogicOp(CtCodeGen::LogicOpType::And); break;
		case Bin::LogicOr:
			op = new CtCodeGen::LogicOp(CtCodeGen::LogicOpType::Or); break;
		case Bin::MemberAccess:
		case Bin::NamespaceAccesss:
		break;
	}

    this->current_function->units.push_back(op);
}


void CtEmitter::handleStmtBlock(CtNode::StmtBlock *node)
{
	for (auto stmt: node->stmts)
	{
		this->walk(stmt);
	}
}


void CtEmitter::handleDeclaration(CtNode::Declaration *node)
{
	this->variables[node->name] = this->variables.size();

	if (node->assignment)
	{
		this->walk(node->assignment);
	}
}


void CtEmitter::handleOut(CtNode::Out *node)
{
	this->walk(node->expr);

	static std::map<CtSpec::PrimitiveT, int> format_specfier =
	{
		{CtSpec::PrimitiveT::Bool,   2},
		{CtSpec::PrimitiveT::Int,    2},
		{CtSpec::PrimitiveT::UInt,   3},
		{CtSpec::PrimitiveT::Float,  4},
	};

	this->current_function->units.push_back(new CtCodeGen::Out(format_specfier[node->expr->expr_type->primitive]));
}


void CtEmitter::handleLoop(CtNode::Loop* node)
{
	auto station = new CtCodeGen::StationOp(this->current_function->station_count++);
	this->current_function->units.push_back(station);
	
	this->walk(node->block);

	auto jump = new CtCodeGen::JumpOp(station->id, CtCodeGen::JumpOpType::Norm);
	this->current_function->units.push_back(jump);
}


void CtEmitter::handleWhile(CtNode::While *node)
{
	auto loop_station = new CtCodeGen::StationOp(this->current_function->station_count++);
	this->current_function->units.push_back(loop_station);

	this->walk(node->condition);

	auto exiting_station = new CtCodeGen::StationOp(this->current_function->station_count++);
	this->current_function->units.push_back(new CtCodeGen::JumpOp(exiting_station->id, CtCodeGen::JumpOpType::False));

	this->walk(node->block);

	this->current_function->units.push_back(new CtCodeGen::JumpOp(loop_station->id, CtCodeGen::JumpOpType::Norm));
	this->current_function->units.push_back(exiting_station);
}


void CtEmitter::handleFor(CtNode::For *node)
{
	this->walk(node->init);

	auto loop_station = new CtCodeGen::StationOp(this->current_function->station_count++);
	this->current_function->units.push_back(loop_station);

	this->walk(node->condition);

	auto exiting_station = new CtCodeGen::StationOp(this->current_function->station_count++);
	this->current_function->units.push_back(new CtCodeGen::JumpOp(exiting_station->id, CtCodeGen::JumpOpType::False));
	
	this->walk(node->block);
	this->walk(node->step);

	this->current_function->units.push_back(new CtCodeGen::JumpOp(loop_station->id, CtCodeGen::JumpOpType::Norm));
	this->current_function->units.push_back(exiting_station);
}


void CtEmitter::handleIf(CtNode::If* node)
{
	auto exiting_station = new CtCodeGen::StationOp(this->current_function->station_count++);

	this->walk(node->condition);
	this->current_function->units.push_back(new CtCodeGen::JumpOp(exiting_station->id, CtCodeGen::JumpOpType::False));

	this->walk(node->then_block);
	auto ran_station = new CtCodeGen::StationOp(this->current_function->station_count++);
	this->current_function->units.push_back(new CtCodeGen::JumpOp(ran_station->id, CtCodeGen::JumpOpType::Norm));

	this->current_function->units.push_back(exiting_station);
	if (node->else_stmt) {this->walk(node->else_stmt);}

	this->current_function->units.push_back(ran_station);
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
	this->walk(node->expr);
	this->current_function->units.push_back(
		new CtCodeGen::TypeCastOp(op_type_map[node->expr->expr_type->primitive], op_type_map[node->expr_type->primitive])
	);
}
