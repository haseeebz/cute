#include <string>
#include <sys/types.h>
#include <vector>

#include "token.hpp"


TokenStream::TokenStream(std::string src)
{
	this->srcStr = src;
	this->curr_token = 0;
}


void TokenStream::add(Token token)
{
	this->tokens.push_back(token);
}


Token TokenStream::next()
{
	if (this->curr_token >= this->tokens.size())
	{
		return Token(TokenType::tokenEOF, 0,0);
	}

	return this->tokens[this->curr_token++];
}


std::string TokenStream::viewToken(Token* token)
{
	std::string str(this->srcStr.substr(token->start, token->end - token->start));
	return str;
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
		case tokenInt: 	  str.append("[ Int ");
		break;
		case tokenFloat:  str.append("[ Float ");
		break;
		case tokenSymbol: str.append("[ Sym ");
		break;
		case tokenWord: str.append("[ Word ");
		break;
		case tokenEOF: str.append("[ EOF ]"); continue;
		break;
		}

		str.append(this->viewToken(tok));
		str.append(" ] ");
    }

	str.append("\n");
	return str;
}