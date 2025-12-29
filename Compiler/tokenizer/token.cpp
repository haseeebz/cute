#include <format>
#include <string>
#include <vector>
#include <sstream>

#include "token.hpp"

#include "../spec/error.hpp"
#include "lang.hpp"


CtTokenStream::CtTokenStream(std::string src)
{
	this->srcStr = src;
	this->curr_token = 0;
}


static inline std::string key_to_str(CtLang::KeyWord keyword)
{
	for (auto key: CtLang::keywordMap)
	{
		if (key.second == keyword) {return key.first;}
	}
	return "keyword";
}


static inline std::string sym_to_str(CtLang::Symbol symbol)
{
	for (auto sym: CtLang::symbolMap)
	{
		if (sym.second == symbol) {return sym.first;}
	}
	return "symbol";
}


static inline std::string token_to_string(CtTokenType token)
{
	switch (token)
	{
        case Int:
			return "int";
        case Float:
			return "float";
        case Word:
			return "word";
        case Symbol:
			return "symbol";
        case Keyword:
			return "keyword";
        case EndOfLine:
			return "EOL";
        case EndOfFile:
			return "EOF";
        case Invalid:
			return "";
        break;
	}
}


void CtTokenStream::raiseError(CtToken* token, std::string msg)
{
	std::istringstream stream(this->srcStr);
    std::string line;

    for (std::size_t i = 0; i <= token->line; ++i)
	{
        if (!std::getline(stream, line))
		{
			line = std::format("Line {} not found! Critical Issue!", token->line);
		}
    }
	
	msg = std::format("{}\nline: {}\n{}", msg, token->line, line);
	CtError::raise(
		CtError::ErrorType::SyntaxError, 
		msg
	);
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
	
	this->raiseError(
		&tok,
		std::format("Expected {} but got {}", token_to_string(t), token_to_string(tok.type))
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
	
	std::string tokens;
	for (auto tok: t)
	{
		tokens.append(token_to_string(tok));
		tokens.append(", ");
	}
	tokens.pop_back();
	tokens.pop_back();

	this->raiseError(
		&tok,
		std::format("Expected {} but got {}", tokens, token_to_string(tok.type))
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


	this->raiseError(
		&tok,
		std::format("Expected word/identifier but got {}", token_to_string(tok.type))
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


	this->raiseError(
		&tok,
		std::format("Expected int but got {}", token_to_string(tok.type))
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


	this->raiseError(
		&tok,
		std::format("Expected float but got {}", token_to_string(tok.type))
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


	this->raiseError(
		&tok,
		std::format("Expected keyword but got {}", token_to_string(tok.type))
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


	this->raiseError(
		&tok,
		std::format("Expected symbol but got {}", token_to_string(tok.type))
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


	this->raiseError(
		&tok,
		std::format("Expected {} but got {}", key_to_str(key), token_to_string(tok.type))
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

	this->raiseError(
		&tok,
		std::format("Expected {} but got {}", sym_to_str(sym), token_to_string(tok.type))
	);
}
