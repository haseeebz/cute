#include <format>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

#include "CuteByte.h"

#include "../parser/node.hpp"

#include "writer.hpp"
#include "../internals.hpp"



void ByteCodeWriter::logToFile(std::string msg)
{
#ifdef CUTE_COMPILER_DEBUG_ENABLED
	static std::ofstream logfile("bytecode.log", std::ios::app);
	logfile << msg << '\n';
#endif
}


void ByteCodeWriter::recurseNode(Node* node)
{
	if (node->type == NodeType::nodeBinaryOp)
	{
		this->recurseNode(node->bop.lhs);
		this->recurseNode(node->bop.rhs);

		CtInstrSize op;
		switch (node->bop.op) 
		{
		case binaryADD: op = instrAddI; logToFile("Add"); break;
		case binarySUB:	op = instrSubI; logToFile("Sub"); break;
		case binaryMUL:	op = instrMulI; logToFile("Mul"); break;
		case binaryDIV: op = instrDivI; logToFile("Div"); break;
		}

		this->instructions.push_back(op);
		return;
	}

	if (node->type == NodeType::nodeInt)
	{
		CtInstrSize num = (CtInstrSize) node->i;
		logToFile(std::format("LoadCoI  {}", num));
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
	std::ofstream stream("bytecode.log");
	stream.close();
	
	this->root = root;
	this->recurseNode(this->root);

	this->instructions.push_back(instrOutI);
	logToFile("OutI");
	this->instructions.push_back(instrHalt);
	logToFile("Halt");
	
	ctDebug(std::format("Bytecode written to file: {}\n", this->outfile));

	this->ctx.instrs = new CtInstrSize[this->instructions.size()];
	this->ctx.instr_count = this->instructions.size();

	for (uint i = 0; i < this->ctx.instr_count; i++)
	{
		this->ctx.instrs[i] = this->instructions[i];
	}

	ProgramContext_write(&this->ctx, this->outfile.data());
	ProgramContext_end(&this->ctx);
}