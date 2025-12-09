#include <string>

#include "../tokenizer/token.hpp"
#include "../parser/parser.hpp"


#pragma once


class CuteCompiler
{
	CtTokenizer tokenizer;
	CtParser parser;
	
	public:

	void compile(std::string filepath, std::string outfile);
};



