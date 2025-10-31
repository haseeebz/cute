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
	tok.start = currIndex;
	
	while (true) 
	{
		c = currSrc[currIndex];

		if (std::isdigit(c))
		{
			currIndex++;
			continue;
		}

		if (c == '.')
		{
			is_float = true;
			currIndex++;
			continue;
		}

		currIndex--;
		break;
	}

	tok.type = is_float ? TokenType::tokenFloat : TokenType::tokenInt;
	tok.len = currIndex - tok.start + 1;


	tokens.push_back(tok);
}


void Tokenizer::tokenizeSymbol()
{
	Token tok(TokenType::tokenSymbol, currIndex, 1);
	tokens.push_back(tok);
}


std::vector<Token> Tokenizer::getTokens()
{
	return tokens;
}


std::string Tokenizer::retrieveToken(Token& token)
{
	std::string tok_str = currSrc.substr(token.start, token.len);
	return tok_str;
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

		std::cout << currSrc.substr(tok.start, tok.len) << "] ";
    }

	std::cout << std::endl;
}