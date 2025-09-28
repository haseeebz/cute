#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"



Token Token_make(TokenType type ,char* str, int len)
{
	Token token;
	token.type = type;
	token.len = len;
	token.str = str;
	return token;
}



void Token_print(Token* token, bool endline)
{
	if (token->type == tokenInt)
	{
		printf("( Int %.*s ) ", token->len, token->str);
	}
	else if (token->type == tokenFloat)
	{
		printf("( Float %.*s ) ", token->len, token->str);
	}
	else if (token->type == tokenSymbol)
	{
		printf("( Sym %.*s ) ", token->len, token->str);
	}
	else if (token->type == tokenWord)
	{
		printf("( Word %.*s ) ", token->len, token->str);
	}
	else if (token->type == tokenEOF)
	{
		printf("( EOF ) ");
	}
	else 
	{
		printf("( Undef %d ) ", token->type);
	}

	if (endline) { printf("\n"); }
}
