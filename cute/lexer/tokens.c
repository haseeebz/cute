#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"


void Token_print(Token* token, bool endline)
{
	if (token->type == tokenInt)
	{
		printf("( Int %d ) ", token->val.i);
	}
	else if (token->type == tokenFloat)
	{
		printf("( Float %lf ) ", token->val.d);
	}
	else if (token->type == tokenSymbol)
	{
		printf("( Sym %c ) ", token->val.c);
	}
	else if (token->type == tokenWord)
	{
		printf("( Word %s ) ", token->val.s);
	}
	else 
	{
		printf("( Undef ) ");
	}

	if (endline) { printf("\n"); }
}


void TokenArray_print(TokenArray* array)
{
	for (int i = 0; i < array->size; i++)
	{
		Token token = array->tokens[i];
		Token_print(&token, false);
	}
	printf("\n");
}


TokenArray* TokenArray_new(int capacity)
{
	TokenArray* array = malloc(sizeof(TokenArray));
	array->tokens = malloc(sizeof(Token)*capacity);
	array->capacity = capacity;
	array->size = 0;
	return array;
}


void TokenArray_del(TokenArray* array)
{
	free(array->tokens);
	free(array);
}


void TokenArray_resize(TokenArray* array, int capacity)
{
	if (capacity <= array->capacity)
	{
		return;
	}

	Token* tokens = malloc(sizeof(Token)*capacity);
	
	for (int i = 0; i <= array->size; i++)
	{
		tokens[i] = array->tokens[i];
	}
	free(array->tokens);
	array->tokens = tokens;
	array->capacity = capacity;
}


bool TokenArray_isEmpty(TokenArray* array)
{
	if (array->size > 0) { return true; }
	return false;
}


void TokenArray_push(TokenArray* array, Token token)
{
	if (array->size >= array->capacity)
	{
		TokenArray_resize(array, array->capacity * 2);	
	}

	array->tokens[array->size] = token;
	array->size++;
}


Token TokenArray_pop(TokenArray* array)
{
	array->size--;
	return array->tokens[array->size];
}