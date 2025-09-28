#include "tokens.h"

#pragma once

typedef struct
{
	char* buffer;
	int length;
	int index;
} Lexer;


Lexer* Lexer_new();
void Lexer_del(Lexer* lexer);
void Lexer_init(Lexer* lexer, char* string);

Token Lexer_nextToken(Lexer* lexer);
void Lexer_backtrack(Lexer* lexer);

Token Lexer_nextToken(Lexer* lexer);
Token Lexer_tokenizeNumber(Lexer* lexer, char* c);
Token Lexer_tokenizeWord(Lexer* lexer, char* c);


