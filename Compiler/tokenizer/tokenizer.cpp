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

		if (std::isalpha(c))
		{
			tokenizeWord();
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
	char sym = currSrc[currIndex];
	Token tok(TokenType::tokenSymbol, (std::string) &sym);
	tokens.push_back(tok);
}

void Tokenizer::tokenizeWord()
{
	std::string str;
	char c;

	while (true)
	{
		c = currSrc[currIndex];

		if (std::isalpha(c))
		{
			str.push_back(c);
			currIndex++;
			continue;
		}

		break;
	}

	Token tok(TokenType::tokenWord, str);
	tokens.push_back(tok);
}


std::vector<Token> Tokenizer::getTokens()
{
	return tokens;
}



std::string Tokenizer::toString()
{
	std::string str;
	Token tok;

	for (uint i = 0; i < tokens.size(); i++)
	{
		tok = tokens[i];

		switch (tok.type) 
		{
		case tokenInt: 	  str.append("[ Int ");
		break;
		case tokenFloat:  str.append("[ Float ");
		break;
		case tokenSymbol: str.append("[ Sym ");
		break;
		case tokenWord: str.append("[ Word ");
		break;
		}

		str.append(tok.str);
		str.append(" ] ");
    }

	str.append("\n");
	return str;
}