#include "tokens.h"

#pragma once

typedef struct
{
	char* curr_str;
	int len_str;
	TokenArray* token_array;
	int index;
} LexerContext;


LexerContext* LexerContext_new();
void LexerContext_del(LexerContext* lexer);
void LexerContext_init(LexerContext* lexer, char* string);

TokenArray* LexerContext_tokenize(LexerContext* lexer);

char LexerContext_nextChar(LexerContext* lexer);
void LexerContext_backtrack(LexerContext* lexer);