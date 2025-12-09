#include <string>

#include "../tokenizer/token.hpp"


#pragma once


class CuteCompiler
{
	CtTokenizer tokenizer;

	
	public:

	void compile(std::string filepath, std::string outfile);
};



