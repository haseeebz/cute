#include <string>
#include <sys/types.h>
#include <vector>

#include "CuteToken.hpp"


TokenStream::TokenStream(std::string src)
{
	this->srcStr = src;
	this->curr_token = 0;
}


void TokenStream::add(Token token)
{
	this->tokens.push_back(token);
}


std::string TokenStream::toString()
{
	Token* tok;
	std::string str;

	for (uint i = 0; i < this->tokens.size(); i++)
	{
		tok = &this->tokens[i];

		switch (tok->type) 
		{
		case tokenInt: 	   str.append("[ Int ");
		break;
		case tokenFloat:   str.append("[ Float ");
		break;
		case tokenSymbol:  str.append("[ Sym ");
		break; 
		case tokenWord:    str.append("[ Word ");
		break;
		case tokenEOF:     str.append("[ EOF ]"); continue;
		break;
		}

		str.append(this->viewToken(tok));
		str.append(" ] ");
    }

	str.append("\n");
	return str;
}


Token TokenStream::next()
{
	if (this->curr_token >= this->tokens.size())
	{
		return Token(TokenType::tokenEOF, 0,0);
	}

	return this->tokens[this->curr_token++];
}

Token TokenStream::peek()
{
	if (this->curr_token >= this->tokens.size())
	{
		return Token(TokenType::tokenEOF, 0,0);
	}

	return this->tokens[this->curr_token];
}


uint TokenStream::currentIndex()
{
	return this->curr_token;
}


void TokenStream::backtrack(uint i)
{
	if (this->curr_token <= 0)
	{
		this->curr_token = 0;
		return;
	}
	this->curr_token -= i;
}


void TokenStream::gotoIndex(uint i)
{
	if (i >= this->tokens.size())
	{
		this->curr_token = this->tokens.size() - 1;
		return;
	}
	this->curr_token = i;
}


std::string TokenStream::viewToken(Token* token)
{
	uint len = token->end - token->start + 1;

	return this->srcStr.substr(token->start, len);
}


char TokenStream::viewSymToken(Token* token)
{
	return this->srcStr[token->start];
}


bool TokenStream::getInt(std::string* i)
{
	Token tok = this->next();

	if (tok.type != TokenType::tokenInt)
	{
		this->backtrack();
		return false;
	}

	*i = this->viewToken(&tok);
	return true;
}


bool TokenStream::getFloat(std::string* d)
{
	Token tok = this->next();

	if (tok.type != TokenType::tokenFloat)
	{
		this->backtrack();
		return false;
	}

	*d = this->viewToken(&tok);
	return true;
}


bool TokenStream::getWord(std::string* str)
{
	Token tok = this->next();

	if (tok.type != TokenType::tokenWord)
	{
		this->backtrack();
		return false;
	}

	*str = this->viewToken(&tok);
	return true;
}


bool TokenStream::getSym(char* sym)
{
	Token tok = this->next();

	if (tok.type != TokenType::tokenSymbol)
	{
		this->backtrack();
		return false;
	}

	*sym = this->viewSymToken(&tok);
	return true;
}


bool TokenStream::getKeyword(std::string keyword)
{
	std::string str;

	if (this->getWord(&str))
	{
		if (str == keyword)
		{
			return true;
		}
		this->backtrack();
	}

	return false;
}


bool TokenStream::getKeySym(char sym)
{
	char c;

	if (this->getSym(&c))
	{
		if (sym == c)
		{
			return true;
		}
		this->backtrack();
	}

	return false;
}


bool TokenStream::expectType(TokenType type)
{
	Token tok = this->next();
	this->backtrack();

	if (tok.type != type)
	{
		return false;
	}

	return true;
}