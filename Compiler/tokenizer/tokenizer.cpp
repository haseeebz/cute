#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


#include "token.hpp"
#include "tokenizer.hpp"


TokenStream Tokenizer::tokenize(std::string input_file)
{
	std::ifstream stream(input_file);

	// TODO : File Check
	std::ostringstream buffer;
	buffer << stream.rdbuf();
	this->currStream = TokenStream(buffer.str());

	this->currSrc = &this->currStream.srcStr;
	
	char c;
	
	for (this->currIndex = 0; this->currIndex < this->currSrc->length(); this->currIndex++)
	{
		c = this->currSrc->at(currIndex);

		if (c == ' ' or c == '\n') {continue;}

		if (std::isdigit(c))
		{
			this->tokenizeNumber();
			continue;
		}

		if (std::isalpha(c))
		{
			this->tokenizeWord();
			continue;
		}

		this->tokenizeSymbol();
	}

	this->currStream.add(Token(TokenType::tokenEOF, 0,0));

	return this->currStream;
}


void Tokenizer::tokenizeNumber()
{
	bool is_float = false;
	char c;
	uint start, end;
	start = this->currIndex;
	
	while (true) 
	{
		if (this->currIndex >= this->currSrc->length()) {break;}
		c = this->currSrc->at(currIndex);

		if (std::isdigit(c))
		{
			this->currIndex++;
			continue;
		}

		if (c == '.')
		{
			is_float = true;
			this->currIndex++;
			continue;
		}
		break;
	}

	this->currIndex--;
	end = this->currIndex;

	TokenType type = is_float ? TokenType::tokenFloat : TokenType::tokenInt;
	
	this->currStream.add(Token(type, start, end));
}


void Tokenizer::tokenizeSymbol()
{
	this->currStream.add(Token(TokenType::tokenSymbol, this->currIndex, this->currIndex));
}


void Tokenizer::tokenizeWord()
{
	char c;
	uint start, end;
	start = this->currIndex;

	while (true)
	{
		if (this->currIndex >= this->currSrc->length()) {break;}
		c = this->currSrc->at(currIndex);

		if (std::isalpha(c) || std::isdigit(c))
		{
			this->currIndex++;
			continue;
		}

		break;
	}

	this->currIndex--;
	end = this->currIndex;

	this->currStream.add(Token(TokenType::tokenWord, start, end));
}

