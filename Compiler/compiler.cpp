#include "CuteByte.h"
#include "CuteCompiler.hpp"
#include "parser/node.hpp"

#include <cctype>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "internals.hpp"
#include "tokenizer/token.hpp"


void CuteCompiler::compile(std::string filepath, std::string outfile)
{
	TokenStream stream = tokenizer.tokenize(filepath);

	ctDebug("Tokenized Source:\n");
	ctDebug(stream.toString());

	
	ctNode* root = parser.parse(&stream);
	
	ctDebug("Parsed Code:\n")
	PrintVisitor printer;
	root->accept(&printer);

	//ctDebug(root->str());

	/*
	writer.setOutFile(outfile);
	writer.write(root);

	delete root;*/
}


void CuteCompiler::assemble(std::string filepath, std::string outfile)
{
	std::map<std::string, ctInstr> ByteCodeMap = 
	{
		{"Halt", instrHalt},
		{"LoadCoI", instrLoadCoI},
		{"AddI", instrAddI},
		{"SubI", instrSubI},
		{"MulI", instrMulI},
		{"DivI", instrDivI},
		{"OutI", instrOutI},
		{"StoreI", instrStoreI},
		{"LoadI", instrLoadI}
	};

	std::ifstream stream(filepath);
	std::ostringstream buffer;
	buffer << stream.rdbuf();
	
	std::string raw = buffer.str();
	
	std::vector<std::string> codes;

	uint index = 0;
	for (uint i = 0; i < raw.length(); i++)
	{
		char c = raw[i];
		if (c == ' ' or c == '\n')
		{
			codes.push_back(raw.substr(index, i - index));
			index = i + 1;
		}
	}

	for (std::string code: codes)
	{std::cout << code << std::endl;}
	
	std::vector<ctInstrSize> instrs;

	for (std::string code: codes)
	{
		
		if (ByteCodeMap.contains(code))
		{
			instrs.push_back(ByteCodeMap[code]);
			continue;
		}
		// I'll assume for now that if it is not in the Map, its an integar

		instrs.push_back(std::stoi(code));
	}

	ctProgramImage img;

	img.header.instr_count = instrs.size();
	img.instrs = instrs.data();
	img.main.local_var_space = 10;
	img.main.arg_count = 0;
	img.main.id = 0;

	ctProgramImage_write(&img, outfile.data());
}