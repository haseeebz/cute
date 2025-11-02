#include <string>

#include "../tokenizer/tokenizer.hpp"
#include "../parser/parser.hpp"
#include "../writer/writer.hpp"


#pragma once


class CuteCompiler
{
	Tokenizer tokenizer;
	Parser parser;
	ByteCodeWriter writer;
	
	public:

	void compile(std::string filepath);
};



