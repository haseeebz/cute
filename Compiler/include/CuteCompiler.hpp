#include <string>

#include "../tokenizer/token.hpp"
#include "../parser/parser.hpp"
#include "../emitter/emitter.hpp"


#pragma once


class CuteCompiler
{
	CtTokenizer tokenizer;
	CtParser parser;
	CtEmitter emitter;

	public:

	void compile(std::string filepath, std::string outfile);
};



