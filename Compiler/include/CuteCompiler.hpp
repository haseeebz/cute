#include <string>

#include "../tokenizer/token.hpp"
#include "../parser/parser.hpp"
#include "../resolver/resolver.hpp"

#pragma once

#define CUTE_VERSION "v0.0.7"

void exec_test();

class CuteCompiler
{
	CtTokenizer tokenizer;
	CtParser parser;
	CtResolver resolver;

	public:

	void invokeComponent(std::string filepath, std::string comp);
	void compile(std::string filepath, std::string outfile);

};



