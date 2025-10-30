#include <sys/types.h>
#include <vector>

#include "token.hpp"


#pragma once 

class Tokenizer 
{
	std::vector<Token> tokens;

	uint strIndex;
	std::string currStr;

	public:

	void tokenize(std::string str);
	void tokenizeNumber();
	void tokenizeSymbol();

	std::vector<Token> getTokens();
	void printTokens();
};