#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "lang.hpp"
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

		if (c == ' ' || c == '\t') {continue;}

		if (c == '\n' || c == CtLang::EOL)
		{
			this->currStream.add(CtToken(CtTokenType::EndOfLine, 0, 0));
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
	int start = currIndex;
	int end;

	sym.push_back(this->currSrc->at(currIndex));

	if (!CtLang::symbolMap.contains(sym))
	{
		this->currStream.add(CtToken(CtTokenType::Invalid));
		return;
	}

	currIndex++;
	end = start;

	if (this->currIndex < this->currSrc->length()) 
	{
		sym.push_back(this->currSrc->at(currIndex));
		end++;

		if (!CtLang::symbolMap.contains(sym))
		{
			end--;
			currIndex--;
			sym.pop_back();
		}
	}

	
	CtToken token(CtTokenType::Symbol, start, end);
	token.val.sym = CtLang::symbolMap[sym];
	this->currStream.add(token);
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

	CtToken token;

	if (CtLang::keywordMap.contains(str))
	{
		token.type = CtTokenType::Keyword;
		token.view.start = start;
		token.view.end = end;
		token.val.keyword = CtLang::keywordMap[str];
		this->currStream.add(token);
	}
	else 
	{
		token.type = CtTokenType::Word;
		token.view.start = start;
		token.view.end = end;
		this->currStream.add(token);
	}
	
}

