#include "CuteByte.h"
#include "../node/node.hpp"

#include <iostream>
#include <string>

#include "emitter.hpp"



void CtEmitter::write(std::string outfile)
{
	ctImageError err = ctProgramImage_write(&this->img, outfile.data());
}


void CtEmitter::emit(CtNode::RootProgram *root, std::string outfile)
{
	this->walk(root);

	this->write(outfile);
}


void CtEmitter::handleRoot(CtNode::RootProgram *node)
{
	this->walk(node->src);
}


void CtEmitter::handleSource(CtNode::Source *node)
{
	this->walk(node->functions["main"]);

	this->img.header.func_count = 1;
	this->img.header.instr_count = this->instrs.size();
	this->img.header.const_count = 0;

	this->img.instrs = this->instrs.data();
}


void CtEmitter::handleFunction(CtNode::Function *node)
{
	for (auto stmt: node->statements)
	{
		this->walk(stmt);
	}	

	this->instrs.push_back(instrExit);

	ctInstrSize packed[4];
	int i = 0;
	ctProgramImage_packInt32(&i, packed);

	for (int i = 0; i < 4; i++) {this->instrs.push_back(packed[i]);}


	ctFuncMetadata meta;
	meta.func_id = 0;
	meta.args_count = 0;
	meta.locals_count = this->variables.size();
	meta.instr_address = 0;

	this->img.func_table = new ctFuncMetadata(meta);
}


void CtEmitter::handleInt(CtNode::Int *node)
{
	this->instrs.push_back(instrLoadCoI32);
	
	ctInstrSize packed[4];
	int i = std::stoi(node->raw);
	ctProgramImage_packInt32(&i, packed);

	for (int i = 0; i < 4; i++) {this->instrs.push_back(packed[i]);}

}


void CtEmitter::handleBinaryOp(CtNode::BinaryOp *node)
{
	this->walk(node->left);
	this->walk(node->right);

	ctInstr op;

	switch (node->op)
	{
		case CtLang::Symbol::Plus:       op = (node->result_type == "i32") ?  instrAddI32:instrAddF32; break;
		case CtLang::Symbol::Minus:      op = (node->result_type == "i32") ?  instrSubI32:instrSubF32; break;
		case CtLang::Symbol::Star:       op = (node->result_type == "i32") ?  instrMulI32:instrMulF32; break;
		case CtLang::Symbol::Slash:      op = (node->result_type == "i32") ?  instrDivI32:instrDivF32; break;
		case CtLang::Symbol::Percentage: op = instrModI32; break;
	}

	this->instrs.push_back(op);
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

	this->instrs.push_back(instrOut);
	int i = format_specfier[node->expr->result_type];
	ctInstrSize packed[4];
	ctProgramImage_packInt32(&i, packed);
	for (int i = 0; i < 4; i++) {this->instrs.push_back(packed[i]);}
}


void CtEmitter::handleAssignment(CtNode::Assignment *node)
{
	this->walk(node->value);

	this->instrs.push_back(instrStoreI32);
	ctInstrSize packed[4];
	int i = this->variables[node->name->val];
	ctProgramImage_packInt32(&i, packed);
	for (int i = 0; i < 4; i++) {this->instrs.push_back(packed[i]);}

	// to keep assignment an expression, we need to have it return some value, this is just for consistency, might remove later.
	this->instrs.push_back(instrLoadI32);
	i = this->variables[node->name->val];
	ctProgramImage_packInt32(&i, packed);
	for (int i = 0; i < 4; i++) {this->instrs.push_back(packed[i]);}
}



void CtEmitter::handleIdentifier(CtNode::Identifier *node)
{
	this->instrs.push_back(instrLoadI32);
	ctInstrSize packed[4];
	int i = this->variables[node->val];
	ctProgramImage_packInt32(&i, packed);
	for (int i = 0; i < 4; i++) {this->instrs.push_back(packed[i]);}
}


void CtEmitter::handleTypeCast(CtNode::TypeCast *node)
{
	static std::map<std::string, ctInstr> cast_map = 
	{
		{"f32i32", instrF32I32},
		{"i32f32", instrI32F32},
		{"i64f64", instrI64F64},
		{"f64i64", instrF64I64},
		{"f32f64", instrF32F64},
		{"f64f32", instrF64F32},
		{"i32i64", instrI32I64},
		{"i64i32", instrI64I32}
	};

	this->walk(node->expr);
	auto typecast = node->expr->result_type + node->to_type;
	auto instr = cast_map[typecast];
	this->instrs.push_back(instr);
}
