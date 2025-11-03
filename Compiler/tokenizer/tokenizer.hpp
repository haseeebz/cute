#include <string>
#include <vector>
#include <sys/types.h>

#include "token.hpp"

#pragma once 

class Tokenizer 
{
	std::vector<Token> tokens;

	uint currIndex;
	std::string currSrc;

	public:

	void tokenize(std::string input_file);
	void tokenizeNumber();
	void tokenizeSymbol();

	std::vector<Token> getTokens();
	std::string retrieveToken(Token& token);
	
	std::string toString();
};