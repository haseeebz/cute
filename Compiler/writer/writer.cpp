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


void ByteCodeWriter::recurseNode(Node *node)
{
	if (node->type == NodeType::nodeBinaryOp)
	{
		bool assign = false;
		this->recurseNode(node->bop.rhs);

		ctInstrSize op;
		switch (node->bop.op) 
		{
		case binaryADD: op = instrAddI; logToFile("Add"); break;
		case binarySUB:	op = instrSubI; logToFile("Sub"); break;
		case binaryMUL:	op = instrMulI; logToFile("Mul"); break;
		case binaryDIV: op = instrDivI; logToFile("Div"); break;
		case binaryASSIGN: op = instrStoreI; assign = true; logToFile("Store"); break;
		}


	
		if (!assign) {this->recurseNode(node->bop.lhs);}
		else {
			if (!idf_map.contains(node->bop.lhs->idf))
			{
				idf_map[node->bop.lhs->idf] = idf_id;
				idf_id++;
			}

			int id = idf_map[node->bop.lhs->idf];
			ctInstrSize num = (ctInstrSize) id;
			logToFile(std::format("{}", num));
			this->instructions.push_back(num);
		}

		this->instructions.push_back(op);
		return;
	}

	if (node->type == NodeType::nodeIdentifier)
	{
		logToFile(std::format("LoadI"));
		this->instructions.push_back(instrLoadI);

		if (!idf_map.contains(node->idf))
		{
			idf_map[node->idf] = idf_id;
			idf_id++;
		}

		int id = idf_map[node->idf];
		ctInstrSize num = (ctInstrSize) id;
		logToFile(std::format("{}", num));
		this->instructions.push_back(num);
		return;
	}

	if (node->type == NodeType::nodeInt)
	{
		ctInstrSize num = (ctInstrSize) node->i;
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


void ByteCodeWriter::write(Node *root)
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

	this->img.instrs = new ctInstrSize[this->instructions.size()];

	this->img.header.instr_count = this->instructions.size();

	for (uint i = 0; i < this->img.header.instr_count; i++)
	{
		this->img.instrs[i] = this->instructions[i];
	}

	ctProgramImage_write(&this->img, this->outfile.data());
}