#include <string>
#include <sys/types.h>
#pragma once 



enum TokenType 
{
	tokenInt,
	tokenFloat,
	tokenSymbol,
	tokenWord
};


struct Token
{
	TokenType type;
	std::string str;

	Token() = default;
	Token(TokenType t, std::string s) : type(t), str(s) {};
};

