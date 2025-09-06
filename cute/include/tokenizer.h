#include <stdbool.h>
#include "containers.h"

#pragma once

typedef struct {
	char* current_string;
	int index;
	int string_size;
	ContainerStack* stack;
	Container previous_token;
} TokenizerContext;



TokenizerContext* newTokenizerContext(char* string);
void delTokenizerContext(TokenizerContext* tokenizer);

char nextToken(TokenizerContext* tokenizer);
void backtrackToken(TokenizerContext* tokenizer);

ContainerStack* tokenize(char* string);
void tokenizeNumber(TokenizerContext* tokenizer, char c);
