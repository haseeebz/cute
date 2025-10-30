#include <string>
#pragma once 



enum TokenType 
{
	tokenInt,
	tokenFloat,
	tokenSymbol
};


struct Token
{
	TokenType type;
	std::string str;

	Token() = default;
	Token(TokenType t, std::string s);
};

