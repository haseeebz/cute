#include <vector>

#include "token.hpp"


#pragma once 

class Tokenizer 
{
	std::vector<Token> tokens;

	public:

	void tokenize();
	std::vector<Token> getTokens();
};