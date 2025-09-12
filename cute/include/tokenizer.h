#include <stdbool.h>
#include "atom.h"

#pragma once

typedef struct {
	char* current_string;
	int index;
	int string_size;
	CuteAtomStack* stack;
} TokenizerContext;



TokenizerContext* TokenizerContext_new();
void TokenizerContext_init(TokenizerContext* tokenizer, char* string);
void TokenizerContext_del(TokenizerContext* tokenizer);

char TokenizerContext_nextToken(TokenizerContext* tokenizer);
void TokenizerContext_backtrackToken(TokenizerContext* tokenizer);

CuteAtomStack* TokenizerContext_tokenize(TokenizerContext* tokenizer, char* string);
void TokenizerContext_tokenizeNumber(TokenizerContext* tokenizer, char c);
void TokenizerContext_tokenizeSymbol(TokenizerContext* tokenizer, char c);

