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
	
	for (currIndex = 0; currIndex < currSrc->length(); currIndex++)
	{
		c = currSrc->at(currIndex);

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

	this->currStream.add(Token(TokenType::tokenEOF, 0,0));

	return this->currStream;
}


void Tokenizer::tokenizeNumber()
{
	bool is_float = false;
	char c;
	uint start, end;
	start = currIndex;
	
	while (true) 
	{
		if (currIndex > currSrc->length()) {break;}
		c = currSrc->at(currIndex);

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
		break;
	}

	currIndex--;
	end = currIndex;

	TokenType type = is_float ? TokenType::tokenFloat : TokenType::tokenInt;
	
	this->currStream.add(Token(type, start, end));
}


void Tokenizer::tokenizeSymbol()
{
	this->currStream.add(Token(TokenType::tokenSymbol, currIndex, currIndex));
}


void Tokenizer::tokenizeWord()
{
	char c;
	uint start, end;
	start = currIndex;

	while (true)
	{
		if (currIndex > currSrc->length()) {break;}
		c = currSrc->at(currIndex);

		if (std::isalpha(c))
		{
			currIndex++;
			continue;
		}

		break;
	}

	currIndex--;
	end = currIndex;

	this->currStream.add(Token(TokenType::tokenWord, start, end));
}

