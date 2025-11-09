#include <string>
#include <vector>
#include <sys/types.h>

#include "token.hpp"

#pragma once 

class Tokenizer 
{
	TokenStream currStream;

	std::string* currSrc;
	uint currIndex;

	public:

	TokenStream tokenize(std::string input_file);
	void tokenizeNumber();
	void tokenizeSymbol();
	void tokenizeWord();
};