#include <stdbool.h>

#pragma once
#define WORD_LEN 10

typedef enum
{
	tokenInt,
	tokenFloat,
	tokenSymbol,
	tokenWord
} TokenType;


typedef struct
{
	TokenType type;
	union {
		int i;
		char c;
		char s[WORD_LEN];
		double d;
	} val;
} Token;

void Token_print(Token* token, bool endline);

typedef struct
{
	Token* tokens;
	int size;
	int capacity;
} TokenArray;

void TokenArray_print(TokenArray* array);
TokenArray* TokenArray_new(int capacity);
void TokenArray_del(TokenArray* array);
void TokenArray_resize(TokenArray* array, int capacity);
bool TokenArray_isEmpty(TokenArray* array);
void TokenArray_push(TokenArray* array, Token token);
Token TokenArray_pop(TokenArray* array);