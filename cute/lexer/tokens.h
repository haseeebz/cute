#include <stdbool.h>

#pragma once

typedef enum
{
	tokenInt,
	tokenSymbol
} TokenType;

typedef struct
{
	TokenType type;
	union {
		int i;
		char c;
	} val;
} Token;

void Token_print(Token* token, bool endline);

typedef struct
{
	Token* tokens;
	int size;
	int capacity;
} TokenStack;

TokenStack* TokenStack_new(int capacity);
void TokenStack_del(TokenStack* stack);
void TokenStack_resize(TokenStack* stack, int capacity);
bool TokenStack_isEmpty(TokenStack* stack);
void TokenStack_push(TokenStack* stack, Token token);
Token TokenStack_pop(TokenStack* stack);