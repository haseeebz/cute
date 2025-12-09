#include <string>

#include "CuteToken.hpp"


#pragma once


class CuteCompiler
{
	Tokenizer tokenizer;

	
	public:

	void compile(std::string filepath, std::string outfile);
};



