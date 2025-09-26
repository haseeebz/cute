#include "tokens.h"

#pragma once

typedef struct
{
	char* buffer;
	int length;
	int index;
} LexerContext;


LexerContext* LexerContext_new();
void LexerContext_del(LexerContext* lexer);
void LexerContext_init(LexerContext* lexer, char* string);

Token LexerContext_nextToken(LexerContext* lexer);

Token LexerContext_nextToken(LexerContext* lexer);
Token LexerContext_tokenizeNumber(LexerContext* lexer, char* c);
Token LexerContext_tokenizeWord(LexerContext* lexer, char* c);


