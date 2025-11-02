#include <string>

#include "../tokenizer/tokenizer.hpp"
#include "../parser/parser.hpp"


#pragma once


class CuteCompiler
{
	Tokenizer tokenizer;
	Parser parser;
	
	public:

	void compile(std::string filepath);
};



