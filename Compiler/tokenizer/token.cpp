#include <string>
#include <vector>

#include "token.hpp"


CtTokenStream::CtTokenStream(std::string src)
{
	this->srcStr = src;
	this->curr_token = 0;
}

const std::string* CtTokenStream::source()
{
	return &this->srcStr;
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
		case CtTokenType::Int: 	     str.append("[ Int ");
		break;
		case CtTokenType::Float:     str.append("[ Float "); 
		break; 
		case CtTokenType::Word:      str.append("[ Word "); 
		break;
		case CtTokenType::EndOfLine: str.append("[ EOL ]"); continue;
		break;
		case CtTokenType::EndOfFile: str.append("[ EOF ]"); continue;
		break;
		case CtTokenType::Keyword:	 str.append("[ Key "); 
		break;
		case CtTokenType::Symbol:    str.append("[ Sym "); 
		break;
		case CtTokenType::Invalid:   str.append("[ Invalid ]"); continue;
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
	uint len = token->view.end - token->view.start + 1;
	return this->srcStr.substr(token->view.start, len);
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


bool CtTokenStream::getKeyword(CtSpec::KeyWord *key)
{
	CtToken tok = this->next();

	if (tok.type != CtTokenType::Keyword)
	{
		this->backtrack();
		return false;
	}

	*key = tok.val.keyword;
	return true;
}



bool CtTokenStream::getSymbol(CtSpec::Symbol *sym)
{
	CtToken tok = this->next();

	if (tok.type != CtTokenType::Symbol)
	{
		this->backtrack();
		return false;
	}

	*sym = tok.val.sym;
	return true;
}



bool CtTokenStream::expectKeyword(CtSpec::KeyWord key)
{
	CtToken tok = this->next();
	
	if (tok.val.keyword != key)
	{
		this->backtrack();
		return false;
	}

	return true;
}


bool CtTokenStream::expectSymbol(CtSpec::Symbol sym)
{
	CtToken tok = this->next();
	
	if (tok.val.sym != sym)
	{
		this->backtrack();
		return false;
	}

	return true;
}


bool CtTokenStream::expectType(CtTokenType type, CtToken *token)
{
	CtToken tok = this->next();

	if (tok.type != type)
	{	
		return false;
	}

	if (token != NULL)
	{
		*token = tok;
	}
	
	return true;
}
