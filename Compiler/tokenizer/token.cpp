#include <format>
#include <string>
#include <vector>

#include "token.hpp"

#include "../spec/error.hpp"


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
	if (token->type == CtTokenType::EndOfFile or token->type == CtTokenType::EndOfLine)
	{
		return "EOL/EOF";
	}
	uint len = token->view.end - token->view.start + 1;
	return this->srcStr.substr(token->view.start, len);
}
	

bool CtTokenStream::getType(CtTokenType t, CtToken *token)
{
	CtToken tok = this->next();

	if (tok.type == t)
	{
		if (token != nullptr) {*token = tok;}
		return true;
	}

	this->backtrack();
	return false;
}


bool CtTokenStream::getTypes(std::vector<CtTokenType> t, CtToken *token)
{
	CtToken tok = this->next();

	for (auto type: t)
	{
		if (tok.type == type)
		{
			if (token != nullptr) {*token = tok;}
			return true;
		}
	}

	this->backtrack();
	return false;
}


bool CtTokenStream::getWord(std::string *str)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Word)
	{
		*str = this->viewToken(&tok);
		return true;
	}

	this->backtrack();
	return false;
}


bool CtTokenStream::getInt(std::string *d)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Int)
	{
		*d = this->viewToken(&tok);
		return true;
	}

	this->backtrack();
	return false;
}


bool CtTokenStream::getFloat(std::string *f)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Float)
	{
		*f = this->viewToken(&tok);
		return true;
	}

	this->backtrack();
	return false;
}


bool CtTokenStream::getKeyword(CtLang::KeyWord *key)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Keyword)
	{
		*key = tok.val.keyword;
		return true;
	}

	this->backtrack();
	return false;
}


bool CtTokenStream::getSymbol(CtLang::Symbol *sym)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Keyword)
	{
		*sym = tok.val.sym;
		return true;
	}

	this->backtrack();
	return false;
}


bool CtTokenStream::getKeywordSpecific(CtLang::KeyWord key)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Keyword)
	{
		if (tok.val.keyword == key)
		{
			return true;
		}
	}

	this->backtrack();
	return false;
}


bool CtTokenStream::getSymbolSpecific(CtLang::Symbol sym)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Symbol)
	{
		if (tok.val.sym == sym)
		{
			return true;
		}
	}

	this->backtrack();
	return false;
}



void CtTokenStream::expectType(CtTokenType t, CtToken *token)
{
	CtToken tok = this->next();

	if (tok.type == t)
	{
		if (token != nullptr) {*token = tok;}
		return;
	}

	this->backtrack();
	
	CtError::raise(
		CtError::ErrorType::SyntaxError, 
		"Unexpected Token"
	);
}


void CtTokenStream::expectTypes(std::vector<CtTokenType> t, CtToken *token)
{
	CtToken tok = this->next();

	for (auto type: t)
	{
		if (tok.type == type)
		{
			if (token != nullptr) {*token = tok;}
			return;
		}
	}

	this->backtrack();
	
	CtError::raise(
		CtError::ErrorType::SyntaxError, 
		"Unexpected Token"
	);
}


void CtTokenStream::expectWord(std::string *str)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Word)
	{
		*str = this->viewToken(&tok);
		return;
	}

	this->backtrack();

	CtError::raise(
		CtError::ErrorType::SyntaxError, 
		"Unexpected token."
	);
}


void CtTokenStream::expectInt(std::string *d)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Int)
	{
		*d = this->viewToken(&tok);
		return;
	}

	this->backtrack();

	CtError::raise(
		CtError::ErrorType::SyntaxError, 
		"Unexpected Token Int"
	);
}


void CtTokenStream::expectFloat(std::string *f)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Float)
	{
		*f = this->viewToken(&tok);
		return;
	}

	this->backtrack();

	CtError::raise(
		CtError::ErrorType::SyntaxError, 
		"Unexpected Token Float"
	);
}


void CtTokenStream::expectKeyword(CtLang::KeyWord *key)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Keyword)
	{
		*key = tok.val.keyword;
		return;
	}

	this->backtrack();

	CtError::raise(
		CtError::ErrorType::SyntaxError, 
		"Unexpected Token Keyword"
	);
}


void CtTokenStream::expectSymbol(CtLang::Symbol *sym)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Symbol)
	{
		*sym = tok.val.sym;
		return;
	}

	this->backtrack();

	CtError::raise(
		CtError::ErrorType::SyntaxError, 
		"Unexpected Token Symbol"
	);
}


void CtTokenStream::expectKeywordSpecific(CtLang::KeyWord key)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Keyword)
	{
		if (tok.val.keyword == key)
		{
			return;
		}
	}

	this->backtrack();

	CtError::raise(
		CtError::ErrorType::SyntaxError, 
		"Unexpected Token Specific keyword"
	);
}


void CtTokenStream::expectSymbolSpecific(CtLang::Symbol sym)
{
	CtToken tok = this->next();

	if (tok.type == CtTokenType::Symbol)
	{
		if (tok.val.sym == sym)
		{
			return;
		}
	}

	this->backtrack();

	CtError::raise(
		CtError::ErrorType::SyntaxError, 
		"Unexpected Token Symbol specific"
	);
}
