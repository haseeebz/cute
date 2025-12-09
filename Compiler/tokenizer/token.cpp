#include <string>
#include <sys/types.h>
#include <vector>

#include "token.hpp"


CtTokenStream::CtTokenStream(std::string src)
{
	this->srcStr = src;
	this->curr_token = 0;
}


void CtTokenStream::add(CtToken token)
{
	this->tokens.push_back(token);
}


std::string CtTokenStream::toString()
{
	CtToken *tok;
	std::string str;

	for (uint i = 0; i < this->tokens.size(); i++)
	{
		tok = &this->tokens[i];

		switch (tok->type) 
		{
		case Int: 	   str.append("[ Int ");
		break;
		case Float:      str.append("[ Float ");
		break; 
		case Symbol:    str.append("[ Sym ");
		break; 
		case Word:      str.append("[ Word ");
		break;
		case EndOfFile: str.append("[ EOF ]"); continue;
		break;
		}

		str.append(this->viewToken(tok));
		str.append(" ] ");
    }

	str.append("\n");
	return str;
}


CtToken CtTokenStream::next()
{
	if (this->curr_token >= this->tokens.size())
	{
		return CtToken(CtTokenType::EndOfFile, 0,0);
	}

	return this->tokens[this->curr_token++];
}

CtToken CtTokenStream::peek()
{
	if (this->curr_token >= this->tokens.size())
	{
		return CtToken(CtTokenType::EndOfFile, 0,0);
	}

	return this->tokens[this->curr_token];
}


uint CtTokenStream::currentIndex()
{
	return this->curr_token;
}


void CtTokenStream::backtrack(uint i)
{
	if (this->curr_token <= 0)
	{
		this->curr_token = 0;
		return;
	}
	this->curr_token -= i;
}


void CtTokenStream::gotoIndex(uint i)
{
	if (i >= this->tokens.size())
	{
		this->curr_token = this->tokens.size() - 1;
		return;
	}
	this->curr_token = i;
}


std::string CtTokenStream::viewToken(CtToken *token)
{
	uint len = token->end - token->start + 1;

	return this->srcStr.substr(token->start, len);
}


char CtTokenStream::viewSymToken(CtToken *token)
{
	return this->srcStr[token->start];
}


bool CtTokenStream::getInt(std::string *i)
{
	CtToken tok = this->next();

	if (tok.type != CtTokenType::Int)
	{
		this->backtrack();
		return false;
	}

	*i = this->viewToken(&tok);
	return true;
}


bool CtTokenStream::getFloat(std::string *d)
{
	CtToken tok = this->next();

	if (tok.type != CtTokenType::Float)
	{
		this->backtrack();
		return false;
	}

	*d = this->viewToken(&tok);
	return true;
}


bool CtTokenStream::getWord(std::string *str)
{
	CtToken tok = this->next();

	if (tok.type != CtTokenType::Word)
	{
		this->backtrack();
		return false;
	}

	*str = this->viewToken(&tok);
	return true;
}


bool CtTokenStream::getSym(char *sym)
{
	CtToken tok = this->next();

	if (tok.type != CtTokenType::Symbol)
	{
		this->backtrack();
		return false;
	}

	*sym = this->viewSymToken(&tok);
	return true;
}


bool CtTokenStream::getKeyword(std::string keyword)
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


bool CtTokenStream::getKeySym(char sym)
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


bool CtTokenStream::expectType(CtTokenType type)
{
	CtToken tok = this->next();
	this->backtrack();

	if (tok.type != type)
	{
		return false;
	}

	return true;
}