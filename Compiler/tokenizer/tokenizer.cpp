#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


#include "CuteSpec.hpp"
#include "token.hpp"


CtTokenStream CtTokenizer::tokenize(std::string input_file)
{
	std::ifstream stream(input_file);

	std::ostringstream buffer;
	buffer << stream.rdbuf();
	this->currStream = CtTokenStream(buffer.str());

	this->currSrc = this->currStream.source();
	
	char c;
	
	for (this->currIndex = 0; this->currIndex < this->currSrc->length(); this->currIndex++)
	{
		c = this->currSrc->at(currIndex);

		if (c == ' ') {continue;}

		if (c == '\n')
		{
			this->currStream.add(CtToken(CtTokenType::EndOfLine));
			continue;
		}

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
	std::string sym;
	sym.push_back(this->currSrc->at(currIndex++));

	if (!CtSpec::symbolMap.contains(sym))
	{
		this->currStream.add(CtToken(CtTokenType::Invalid));
		return;
	}

	if (this->currIndex < this->currSrc->length()) 
	{
		sym.push_back(this->currSrc->at(currIndex++));

		if (!CtSpec::symbolMap.contains(sym))
		{
			currIndex--;
			sym.pop_back();
		}
	}
	
	this->currStream.add(CtToken(CtSpec::symbolMap[sym]));
}


void CtTokenizer::tokenizeWord()
{
	char c;
	uint start, end;
	start = this->currIndex;

	std::string str;

	while (true)
	{
		if (this->currIndex >= this->currSrc->length()) {break;}
		c = this->currSrc->at(currIndex);

		if (std::isalpha(c) || std::isdigit(c))
		{
			str.push_back(c);
			this->currIndex++;
			continue;
		}

		break;
	}

	this->currIndex--;
	end = this->currIndex;

	if (CtSpec::keywordMap.contains(str))
	{
		this->currStream.add(CtToken(CtSpec::keywordMap[str]));
	}
	else 
	{
		this->currStream.add(CtToken(CtTokenType::Word, start, end));
	}
	
}

