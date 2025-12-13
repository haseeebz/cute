#include "CuteByte.h"
#include "../node/node.hpp"
#include "CuteSpec.hpp"
#include <iostream>
#include <string>

#include "emitter.hpp"



void CtEmitter::write(std::string outfile)
{
	ctImageError err = ctProgramImage_write(&this->img, outfile.data());

	std::cout << "Image success code: " << int(err) << "\n";
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
		case CtSpec::Symbol::Plus:       op = instrAddI32; break;
		case CtSpec::Symbol::Minus:      op = instrSubI32; break;
		case CtSpec::Symbol::Star:       op = instrMulI32; break;
		case CtSpec::Symbol::Slash:      op = instrDivI32; break;
		case CtSpec::Symbol::Percentage: op = instrModI32; break;
	}

	this->instrs.push_back(op);
}


void CtEmitter::handleDeclaration(CtNode::Declaration *node)
{
	this->variables[node->name->val] = this->variables.size();
}


void CtEmitter::handleAssignment(CtNode::Assignment *node)
{
	this->walk(node->value);

	this->instrs.push_back(instrStoreI32);
	ctInstrSize packed[4];
	int i = this->variables[node->name->val];
	ctProgramImage_packInt32(&i, packed);
	for (int i = 0; i < 4; i++) {this->instrs.push_back(packed[i]);}


	this->instrs.push_back(instrLoadI32);
	i = this->variables[node->name->val];
	ctProgramImage_packInt32(&i, packed);
	for (int i = 0; i < 4; i++) {this->instrs.push_back(packed[i]);}

	this->instrs.push_back(instrOut);
	i = 2;
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