#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "CuteByte.h"

#include "../parser/node.hpp"

#include "writer.hpp"


void ByteCodeWriter::recurseNode(Node* node)
{
	if (node->type == NodeType::nodeBinaryOp)
	{
		this->recurseNode(node->bop.lhs);
		this->recurseNode(node->bop.rhs);

		CtInstrSize op;
		switch (node->bop.op) 
		{
		case binaryADD: op = instrAddI; break;
		case binarySUB:	op = instrSubI; break;
		case binaryMUL:	op = instrMulI; break;
		case binaryDIV: op = instrDivI; break;
		}

		this->instructions.push_back(op);
		return;
	}

	if (node->type == NodeType::nodeInt)
	{
		CtInstrSize num = (CtInstrSize) node->i;
		this->instructions.push_back(instrLoadCoI);
		this->instructions.push_back(num);
		return;
	}
}


void ByteCodeWriter::setOutFile(std::string filepath)
{
	outfile = filepath;
}


void ByteCodeWriter::write(Node* root)
{
	this->root = root;
	this->recurseNode(this->root);

	this->instructions.push_back(instrOutI);
	this->instructions.push_back(instrHalt);
	this->ctx.instrs = new CtInstrSize[this->instructions.size()];
	this->ctx.instr_count = this->instructions.size();

	for (uint i = 0; i < this->ctx.instr_count; i++)
	{
		this->ctx.instrs[i] = this->instructions[i];
	}

	ProgramContext_write(&this->ctx, this->outfile.data());
	//ProgramContext_end(&this->ctx);
}