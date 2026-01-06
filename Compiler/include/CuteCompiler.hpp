#include <string>

#include "../tokenizer/token.hpp"
#include "../parser/parser.hpp"
#include "../analyzer/analyzer.hpp"

#pragma once

#define CUTE_VERSION "v0.0.7"

class CuteCompiler
{
	CtTokenizer tokenizer;
	CtParser parser;
	CtAnalyzer analyzer;

	public:

	void invokeComponent(std::string filepath, std::string comp);
	void compile(std::string filepath, std::string outfile);

};



