#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


#include "token.hpp"


CtTokenStream CtTokenizer::tokenize(std::string input_file)
{
	std::ifstream stream(input_file);

	std::ostringstream buffer;
	buffer << stream.rdbuf();
	this->currStream = CtTokenStream(buffer.str());

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

	this->currStream.add(CtToken(CtTokenType::EndOfFile, 0,0));

	return this->currStream;
}


void CtTokenizer::tokenizeNumber()
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

	CtTokenType type = is_float ? CtTokenType::Float : CtTokenType::Int;
	
	this->currStream.add(CtToken(type, start, end));
}


void CtTokenizer::tokenizeSymbol()
{
	this->currStream.add(CtToken(CtTokenType::Symbol, this->currIndex, this->currIndex));
}


void CtTokenizer::tokenizeWord()
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

	this->currStream.add(CtToken(CtTokenType::Word, start, end));
}

