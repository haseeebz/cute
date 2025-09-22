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

char LexerContext_next(LexerContext* lexer);
void LexerContext_backtrack(LexerContext* lexer);

TokenArray* LexerContext_tokenize(LexerContext* lexer);
void LexerContext_tokenizeNumber(LexerContext* lexer, char c);
void LexerContext_tokenizeWord(LexerContext* lexer, char c);


