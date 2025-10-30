#include <string>

#include "../tokenizer/token.hpp"
#include "../tokenizer/tokenizer.hpp"


#pragma once


class CuteCompiler
{
	Tokenizer tokenizer;
	
	public:

	void compile(std::string str);
};



