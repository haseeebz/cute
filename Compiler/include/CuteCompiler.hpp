#include <string>

#include "../tokenizer/tokenizer.hpp"
#include "../parser/parser.hpp"
#include "../assembler/assembler.hpp"
//#include "../writer/writer.hpp"


#pragma once


class CuteCompiler
{
	Tokenizer tokenizer;
	Parser parser;
	CuteAssembler assembler;
	
	//ByteCodeWriter writer;
	
	public:

	

	void compile(std::string filepath, std::string outfile);
	void assemble(std::string filepath, std::string outfile);
};



