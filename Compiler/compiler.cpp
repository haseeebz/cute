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

		{"DupAtom", instrDupAtom},
		{"PopAtom", instrPopAtom},

		{"LoadCoI8", instrLoadCoI8},
		{"LoadCoI32", instrLoadCoI32},
		{"LoadCoI64", instrLoadCoI64},
		{"LoadCoF32", instrLoadCoF32},
		{"LoadCoF64", instrLoadCoF64},

		{"LoadI32", instrLoadI32},
		{"LoadI64", instrLoadI64},
		{"LoadF32", instrLoadF32},
		{"LoadF64", instrLoadF64},

		{"StoreI32", instrStoreI32},
		{"StoreI64", instrStoreI64},
		{"StoreF32", instrStoreF32},
		{"StoreF64", instrStoreF64},

		{"AddI32", instrAddI32},
		{"AddI64", instrAddI64},
		{"AddF32", instrAddF32},
		{"AddF64", instrAddF64},

		{"SubI32", instrSubI32},
		{"SubI64", instrSubI64},
		{"SubF32", instrSubF32},
		{"SubF64", instrSubF64},

		{"MulI32", instrMulI32},
		{"MulI64", instrMulI64},
		{"MulF32", instrMulF32},
		{"MulF64", instrMulF64},

		{"DivI32", instrDivI32},
		{"DivI64", instrDivI64},
		{"DivF32", instrDivF32},
		{"DivF64", instrDivF64},

		{"And", instrAnd},
		{"Or", instrOr},
		{"Not", instrNot},
		{"Xor", instrXor},

		{"CmpI32", instrCmpI32},
		{"CmpI64", instrCmpI64},
		{"CmpF32", instrCmpF32},
		{"CmpF64", instrCmpF64},

		{"Cmp2BoolEq", instrCmp2BoolEq},
		{"Cmp2BoolNe", instrCmp2BoolNe},
		{"Cmp2BoolLt", instrCmp2BoolLt},
		{"Cmp2BoolLe", instrCmp2BoolLe},
		{"Cmp2BoolGt", instrCmp2BoolGt},
		{"Cmp2BoolGe", instrCmp2BoolGe},

		{"Jmp", instrJmp},
		{"JmpTrue", instrJmpTrue},
		{"JmpFalse", instrJmpFalse},

		{"Call", instrCall},
		{"CallVirtual", instrCallVirtual},
		{"Return", instrReturn},

		{"NewCon", instrNewCon},
		{"AccessCon", instrAccessCon},
		{"DelCon", instrDelCon},

		{"Out", instrOut},
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

	std::vector<Constant> consts;
	consts.push_back((Constant) {.i32 =10});
	consts.push_back((Constant) {.i32 =10});

	
	
	for (std::string code: codes)
	{
		
		if (ByteCodeMap.contains(code))
		{
			instrs.push_back(ByteCodeMap[code]);
			continue;
		}
		// I'll assume for now that if it is not in the Map, its an integar

		instrs.push_back((ctInstrSize) std::stoi(code));
	}

	ctProgramImage img;

	img.header.instr_count = instrs.size();
	img.instrs = instrs.data();

	img.header.const_count = consts.size();
	img.consts = consts.data();

	ctImageError code = ctProgramImage_write(&img, outfile.data());

}