#include <sys/types.h>
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
	uint start;
	uint len;

	Token() = default;
	Token(TokenType t, uint start, uint len) : type(t), start(start), len(len) {};
};

