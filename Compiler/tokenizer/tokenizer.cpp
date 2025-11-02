#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


#include "token.hpp"
#include "tokenizer.hpp"


void Tokenizer::tokenize(std::string input_file)
{
	std::ifstream stream(input_file);

	// TODO : File Check
	std::ostringstream buffer;
	buffer << stream.rdbuf();
	currSrc = buffer.str();
	char c;
	
	for (currIndex = 0; currIndex < currSrc.length(); currIndex++)
	{
		c = currSrc[currIndex];

		if (c == ' ' or c == '\n') {continue;}

		if (std::isdigit(c))
		{
			tokenizeNumber();
			continue;
		}

		tokenizeSymbol();
	}
}


void Tokenizer::tokenizeNumber()
{
	bool is_float = false;
	char c;
	Token tok;
	
	
	while (true) 
	{
		c = currSrc[currIndex];

		if (std::isdigit(c))
		{
			tok.str.push_back(c);
			currIndex++;
			continue;
		}

		if (c == '.')
		{
			tok.str.push_back(c);
			is_float = true;
			currIndex++;
			continue;
		}

		currIndex--;
		break;
	}

	tok.type = is_float ? TokenType::tokenFloat : TokenType::tokenInt;
	
	tokens.push_back(tok);
}


void Tokenizer::tokenizeSymbol()
{
	Token tok(TokenType::tokenSymbol, (std::string) &currSrc[currIndex]);
	tokens.push_back(tok);
}


std::vector<Token> Tokenizer::getTokens()
{
	return tokens;
}



void Tokenizer::printTokens()
{
	Token tok;

	for (uint i = 0; i < tokens.size(); i++)
	{
		tok = tokens[i];

		switch (tok.type) 
		{
		case tokenInt: 	  std::cout << "[Int ";
		break;
		case tokenFloat:  std::cout << "[Float ";
		break;
		case tokenSymbol: std::cout << "[Sym ";
		break;
		}

		std::cout << tok.str << "] ";
    }

	std::cout << std::endl;
}