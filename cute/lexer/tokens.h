#include <stdbool.h>

#pragma once
#define WORD_LEN 10

typedef enum
{
	tokenInt,
	tokenFloat,
	tokenSymbol,
	tokenWord,
	tokenEOF
} TokenType;


typedef struct
{
	TokenType type;
	char* str;
	int len;
} Token;

/*
A token refers to a slice of the lexer->buffer that has a specific meaning.
token.str refers to the starting char of the token in the buffer while token.len indicates it's length.
Using this, I don't have to malloc for every fucking token while also getting the advantages of dynamic
string lengths.

Ideally, the parser can just use the token as if it were dynamically allocated. token->str[i] would still work as long as it is less than len. The parser should be able call the nextToken on lexer without 
worrying about all this bs
*/

Token Token_make(TokenType type ,char* str, int len);
void Token_print(Token* token, bool endline);
