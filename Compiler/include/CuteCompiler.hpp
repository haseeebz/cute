#include <string>

#include "../tokenizer/token.hpp"
#include "../parser/parser.hpp"
#include "../analyzer/analyzer.hpp"
#include "../emitter/emitter.hpp"
#include "../bytecode/gen.hpp"


#pragma once


class CuteCompiler
{
	CtTokenizer tokenizer;
	CtParser parser;
	CtAnalyzer analyzer;
	CtEmitter emitter;
	CtBytecodeWriter writer;

	public:

	void compile(std::string filepath, std::string outfile);
};



