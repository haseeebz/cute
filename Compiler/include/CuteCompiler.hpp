#include <string>

#include "../tokenizer/token.hpp"
#include "../parser/parser.hpp"

#pragma once

#define CUTE_VERSION "v0.0.7"

void exec_test();

class CuteCompiler
{
	CtTokenizer tokenizer;
	CtParser parser;

	public:

	void invokeComponent(std::string filepath, std::string comp);
	void compile(std::string filepath, std::string outfile);

};



